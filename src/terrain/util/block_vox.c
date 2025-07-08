// todo: don't use any constants here for numbers
// todo: use voxel scale passed in
// keeps track of the node, position, depth as we dig

void delete_block_entities(ecs_world_t *world, ChunkOctree *node,  byte depth, const byte max_depth) {
    if (unlink_node_ChunkOctree(world, node)) {
        return;
    }
    if (depth != max_depth && node->nodes) {
        depth++;
        for (byte i = 0; i < octree_length; i++) {
            delete_block_entities(world, &node->nodes[i], depth, max_depth);
        }
    }
}

// first check if exists, if it does check if voxel type differs, for removing/adding
// goes through nodes, if not in hashmap, it  will spawn anew
void update_block_entities(ecs_world_t *world, const UpdateBlockEntities *data, NodeDelveData *delve_data) {
    const float voxel_scale = data->scale; // terrain scale
    if (delve_data->depth == delve_data->max_depth) {
        // if null or air, remove
        ChunkOctree *node = delve_data->chunk;
        if (!node) {
            return; // air returns!
        }
        if (!node->value) {
            unlink_node_ChunkOctree(world, node);
            return; // air returns!
        }
        // cheeck if out of bounds
        const byte block_index = node->value - 1;
        if (block_index >= data->block_voxes_count) {
            zox_log_error("block_index out of bounds %i of %i", block_index, data->block_voxes_count)
            return;
        }
        const ecs_entity_t block_prefab = data->block_prefabs[block_index];
        // zox_has(block_meta, BlockPrefabLink);
        // cheeck if vox model - if meta data is block vox type, spawn, otherwise, remove
        if (!block_prefab) {
            unlink_node_ChunkOctree(world, node);
            return;
        }
        // + spawn block vox
        data->spawn_data->position_local = int3_to_byte3(delve_data->octree_position);
        // if exists already, shouldn't we check if is the same block vox type?
        // if exists, and is same type, return!
        if (node->linked == linked_state) {
            const ecs_entity_t e3 = get_node_entity_ChunkOctree(node);
            // ((NodeEntityLink*) node->nodes)->value;
            if (zox_valid(e3)) {
                // this means e3 has spawned
                // we should check its the same one
                // we can add lod to mechanical entities too
                if (zox_has(e3, BlockIndex)) {
                    const byte old_block_index = zox_get_value(e3, BlockIndex)
                    if (old_block_index == block_index) {
                        // zox_log(" > trying to spawn same block vox [%i]\n", old_block_index)
                        // Updates RenderLod of previous Vox Blocks
                        const byte vox_lod = data->spawn_data->render_lod;
                        const byte vox_lod_old = zox_get_value(e3, RenderLod)
                        if (vox_lod_old != vox_lod) {
                            zox_set(e3, RenderLod, { vox_lod })
                            zox_set(e3, ChunkMeshDirty, { chunk_dirty_state_trigger })
                        }
                    }
                }
                return;
            }
        }
        // if not same time, spawn new here
        data->spawn_data->block_index = block_index;
        data->spawn_data->vox = data->block_voxes[block_index];
        float3 position_real = float3_from_int3(delve_data->octree_position);
        float3_multiply_float_p(&position_real, voxel_scale);
        float3_add_float3_p(&position_real, data->chunk_position_real);
        // offset by half
        float3_add_float3_p(&position_real, (float3) { -voxel_scale * 0.5f, -voxel_scale * 0.5f, -voxel_scale * 0.5f });
        if (data->block_vox_offsets[block_index]) {
            float3_add_float3_p(&position_real, (float3) { 0, voxel_scale * -0.25f, 0 });
        }
        data->spawn_data->position_real = position_real;
        // todo: instead of hash, replace OctreeNode with OctreeNodeEntity - link directly in the node
        ecs_entity_t e2;
        // const byte is_world_block = block_prefab && !zox_has(block_prefab, BlockVox);
        data->spawn_data->prefab = block_prefab;
        if (zox_has(block_prefab, BlockVox)) {
            e2 = spawn_block_vox(world, data->spawn_data);
        } else if (zox_has(block_prefab, RendererInstance)) {
            e2 = spawn_block_vox_instanced(world, data->spawn_data);
        } else {
            // dungeon blocks
            e2 = zox_instancee(block_prefab)
            zox_set(e2, ChunkLink, { data->chunk })
            zox_set(e2, VoxelPosition, { delve_data->octree_position })
            // zox_set(e2, Scale1D, { data->spawn_data->scale })
            // zox_set(e2, Position3D, { position_real })
        }
        // finally we link our node to our new block entity
        link_node_ChunkOctree(node, e2);
    } else {
        int3 octree_position = delve_data->octree_position;
        int3_multiply_int_p(&octree_position, 2);
        if (delve_data->chunk && delve_data->chunk->nodes && delve_data->chunk->linked != linked_state) {
            for (byte i = 0; i < octree_length; i++) {
                NodeDelveData delve_data_child = {
                    .chunk = &delve_data->chunk->nodes[i],
                    .octree_position = int3_add(octree_position, octree_positions[i]),
                    .depth = delve_data->depth + 1,
                    .max_depth = delve_data->max_depth
                };
                update_block_entities(world, data, &delve_data_child);
            }
        }
    }
}

// updates during ChunkLodDirty and ChunkMeshDirty events
void update_block_voxes(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t terrain, const ChunkPosition *chunkPosition, const byte vox_lod, const RenderDisabled *renderDisabled, ChunkOctree *chunk, const byte max_depth) {
    float vox_scale = get_terrain_voxel_scale(max_depth);
    float chunk_scale = vox_scale * powers_of_two[max_depth]; // 16.0f
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    const byte block_voxes_count = voxels->length;
    if (block_voxes_count == 0) {
        return;
    }
    ecs_entity_t blocks[block_voxes_count];
    ecs_entity_t block_voxes[block_voxes_count];
    ecs_entity_t block_prefabs[block_voxes_count];
    byte block_vox_offsets[block_voxes_count];
    zero_memory(block_voxes, block_voxes_count, ecs_entity_t)
    zero_memory(block_prefabs, block_voxes_count, ecs_entity_t)
    zero_memory(block_vox_offsets, block_voxes_count, byte)
    //memset(block_voxes, 0, block_voxes_count * sizeof(ecs_entity_t));
    //memset(block_prefabs, 0, block_voxes_count * sizeof(ecs_entity_t));
    //memset(block_vox_offsets, 0, block_voxes_count);
    for (int j = 0; j < block_voxes_count; j++) {
        const ecs_entity_t block = voxels->value[j];
        if (!zox_valid(block)) {
            continue;
        }
        blocks[j] = block;
        if (zox_gett_value(block, BlockModel) == zox_block_vox) {
            block_voxes[j] = zox_get_value(block, ModelLink)
            if (zox_has(block, BlockVoxOffset)) {
                block_vox_offsets[j] = zox_get_value(block, BlockVoxOffset)
            }
        }
        if (zox_has(block, BlockPrefabLink)) {
            block_prefabs[j] = zox_get_value(block, BlockPrefabLink)
        }
    }
    // convert chunk position to real
    const float3 chunk_position_real = float3_add((float3) { vox_scale, vox_scale, vox_scale }, float3_multiply_float(int3_to_float3(chunkPosition->value), chunk_scale));
    SpawnBlockVox spawn_data = {
        .prefab = prefab_block_vox,
        .scale = 0.5f * vox_scale * (float) powers_of_two[max_depth],
        .render_lod = vox_lod,
        .render_disabled = renderDisabled->value // until i get frustum to cull these
    };
    UpdateBlockEntities data = {
        .scale = vox_scale,
        .chunk = e,
        .blocks = blocks, // metas
        .block_prefabs = block_prefabs,
        .block_voxes = block_voxes,
        .block_vox_offsets = block_vox_offsets,
        .block_voxes_count = block_voxes_count,
        .chunk_position_real = chunk_position_real,
        .spawn_data = &spawn_data,
    };
    NodeDelveData delve_data = {
        .chunk = chunk,
        .depth = 0,
        .max_depth = max_depth
    };
    update_block_entities(world, &data, &delve_data);
}
// spawning block vox entities during LOD generation step!
// todo: move this to a render distance dirty step!
// first check if exists, if it does check if voxel type differs, for removing/adding
// goes through nodes, if not in hashmap, it  will spawn anew




    // VoxelNodeDirty ? does VoxelNodeDirty set this?
    // set after node was updated
    /*if (voxel && !is_linked_VoxelNode(node)) {
        // spawn node entity here!
        zox_geter(chunk, VoxLink, voxLink)
        zox_geter(voxLink->value, RealmLink, realmLink)
        zox_geter(realmLink->value, VoxelLinks, voxels)
        const byte block_index = voxel - 1;
        if (block_index >= voxels->length) {
            zox_log_error("voxel [%i] is out of range [%i]", block_index, voxels->length)
            return;
        }
        const ecs_entity_t block = voxels->value[block_index];
        spawned_block_data spawned_data = (spawned_block_data) {
            .block_index = block_index,
            .block = block,
            .position_local = position_local,
            .position_global = position_global,
            .position_real = position_real,
            .chunk = chunk,
            .node = node,
            .scale = scale,
        };
        run_hook_spawned_block(world, &spawned_data);
    }*/

/*void spawn_block_voxes_dive(ecs_world_t *world,
    const UpdateBlockEntities *data,
    NodeDelveData *delve_data)
{
    VoxelNode *node = delve_data->chunk;
    if (!node) {
        return; // air returns!
    }
    if (delve_data->depth != delve_data->max_depth) {
        // did more
        int3 octree_position = delve_data->octree_position;
        int3_multiply_int_p(&octree_position, 2);
        if (has_children_VoxelNode(node)) {
            VoxelNode* kids = get_children_VoxelNode(node);
            for (byte i = 0; i < octree_length; i++) {
                NodeDelveData delve_data_child = {
                    .chunk = &kids[i],
                    .octree_position = int3_add(octree_position, octree_positions[i]),
                    .depth = delve_data->depth + 1,
                    .max_depth = delve_data->max_depth
                };
                spawn_block_voxes_dive(world, data, &delve_data_child);
            }
        }
        return;
    }

    // if null or air, remove
    if (!node->value) {
        //if (is_linked_VoxelNode(node)) {
        //    destroy_node_link_VoxelNode(world, node);
        //}
        return; // air returns!
    }
    // cheeck if out of bounds
    const byte block_index = node->value - 1;
    if (block_index >= data->models_count) {
        zox_log_error("block_index out of bounds %i of %i", block_index, data->models_count)
        return;
    }

    // Remove and return if not a World Block
    const ecs_entity_t block_prefab = data->block_prefabs[block_index];
    if (!block_prefab) {
        destroy_node_link_VoxelNode(world, node);
        return;
    }

    // + spawn block vox
    // if exists already, shouldn't we check if is the same block vox type?
    // if exists, and is same type, return!
    if (is_linked_VoxelNode(node)) {
        return;
    }
    byte3 position_local = int3_to_byte3(delve_data->octree_position);
    // if not same time, spawn new here
    data->spawn_data->block_index = block_index;
    data->spawn_data->vox = data->models[block_index];

    int3 voxel_position = delve_data->octree_position;
    const float scale = data->scale; // terrain scale
    float3 position_real = float3_from_int3(voxel_position);
    float3_scale_p(&position_real, scale);
    float3_add_float3_p(&position_real, data->chunk_position_real);
    // offset by half
    float3_add_float3_p(&position_real, float3_single(-scale * 0.5f));
    //if (data->block_vox_offsets[block_index]) {
    // float3_add_float3_p(&position_real, (float3) { 0, scale * -0.25f, 0 });
    //}
    // data->spawn_data->position_real = position_real;
    // todo: instead of hash, replace OctreeNode with OctreeNodeEntity - link directly in the node
    // ecs_entity_t e2;
    // const byte is_world_block = block_prefab && !zox_has(block_prefab, BlockVox);
    data->spawn_data->prefab = block_prefab;

    if (node->value && !is_linked_VoxelNode(node)) {
        zox_geter(data->chunk, ChunkPosition, chunkPosition)
        zox_geter_value(data->chunk, NodeDepth, byte, node_depth)
        const int chunk_length = powers_of_two[node_depth];
        const int3 chunk_dimensions = int3_single(chunk_length);
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_dimensions);
        int3 position_global = int3_add(voxel_position, chunk_voxel_position);

        // spawn node entity here!
        zox_geter(data->chunk, VoxLink, voxLink)
        zox_geter(voxLink->value, RealmLink, realmLink)
        zox_geter(realmLink->value, VoxelLinks, voxels)
        const byte block_index = node->value - 1;
        if (block_index >= voxels->length) {
            zox_log_error("voxel [%i] is out of range [%i]", block_index, voxels->length)
            return;
        }
        const ecs_entity_t block = voxels->value[block_index];
        spawned_block_data spawned_data = (spawned_block_data) {
            .chunk = data->chunk,
            .node = node,
            .block_index = block_index,
            .block = block,
            .position_local = position_local,
            .position_global = position_global,
            .position_real = position_real,
            .scale = scale,
        };
        run_hook_spawned_block(world, &spawned_data);
    }

    // finally we link our node to our new block entity
    // link_node_VoxelNode(node, e2);
    // zox_log("+ spawned new block in world: %lu", e2)
    // if not linked block
}


// updates during ChunkLodDirty and ChunkMeshDirty events
void spawn_block_voxes(ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t terrain,
    const ChunkPosition *chunkPosition,
    const byte vox_lod,
    const RenderDisabled *renderDisabled,
    VoxelNode *chunk,
    const byte max_depth)
{
    const float vox_scale = get_terrain_voxel_scale(max_depth);
    const float chunk_scale = vox_scale * powers_of_two[max_depth]; // 16.0f
    const float chunk_scale2 = 0.5f * vox_scale * (float) powers_of_two[max_depth];
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    const byte models_count = voxels->length;
    if (models_count == 0) {
        return;
    }
    ecs_entity_t blocks[models_count];
    ecs_entity_t models[models_count];
    ecs_entity_t block_prefabs[models_count];
    byte block_vox_offsets[models_count];
    zero_memory(models, models_count, ecs_entity_t)
    zero_memory(block_prefabs, models_count, ecs_entity_t)
    zero_memory(block_vox_offsets, models_count, byte)
    for (int j = 0; j < models_count; j++) {
        const ecs_entity_t block = voxels->value[j];
        if (!zox_valid(block)) {
            continue;
        }
        blocks[j] = block;
        if (zox_gett_value(block, BlockModel) == zox_block_vox) {
            models[j] = zox_get_value(block, ModelLink)
            if (zox_has(block, BlockVoxOffset)) {
                block_vox_offsets[j] = zox_get_value(block, BlockVoxOffset)
            }
        }
        if (zox_has(block, BlockPrefabLink)) {
            block_prefabs[j] = zox_get_value(block, BlockPrefabLink)
        }
    }
    // convert chunk position to real
    const float3 chunk_position_real = float3_add((float3) { vox_scale, vox_scale, vox_scale }, float3_scale(int3_to_float3(chunkPosition->value), chunk_scale));
    SpawnBlockVox spawn_data = {
        .prefab = prefab_block_vox,
        .scale = chunk_scale2,
        .render_lod = vox_lod,
        .render_disabled = renderDisabled->value // until i get frustum to cull these
    };
    UpdateBlockEntities data = {
        .scale = vox_scale,
        .chunk = e,
        .blocks = blocks, // metas
        .block_prefabs = block_prefabs,
        .models = models,
        .block_vox_offsets = block_vox_offsets,
        .models_count = models_count,
        .chunk_position_real = chunk_position_real,
        .spawn_data = &spawn_data,
    };
    NodeDelveData delve_data = {
        .chunk = chunk,
        .depth = 0,
        .max_depth = max_depth
    };
    spawn_block_voxes_dive(world, &data, &delve_data);
}

// Uses voxelNodeDirty to trigger
void BlockVoxSpawnSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxelNodeDirty)
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(ChunkPosition)
    zox_sys_in(VoxLink)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderDisabled)
    zox_sys_in(RenderLod)
    zox_sys_in(RenderDistance)
    zox_sys_out(VoxelNode)
    zox_sys_out(BlocksSpawned)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(VoxelNodeDirty, voxelNodeDirty)
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(BlocksSpawned, blocksSpawned)
        // either voxel node is dirty, or we are spawning for first time based on distance changes
        if (voxelNodeDirty->value != zox_dirty_active && !(!blocksSpawned->value && renderDistanceDirty->value == zox_dirty_active)) {
            continue;
        }
        //  base off render distance
        if (renderLod->value > block_vox_render_at_lod) {
            continue;
        }
        // zox_log("+ spawning block voxes at [%ix%ix%i]", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
        const byte vox_lod = distance_to_lod_vox_block(renderDistance->value);
        spawn_block_voxes(world,
            e,
            voxLink->value,
            chunkPosition,
            vox_lod,
            renderDisabled,
            voxelNode,
            nodeDepth->value);

        reduce_voxel_nodes(world, voxelNode);

        blocksSpawned->value = 1;
    }
} zox_declare_system(BlockVoxSpawnSystem)*/


        // lods!
        /*if (renderDistanceDirty->value == zox_dirty_active && blocksSpawned->value) {
            const byte vox_lod = distance_to_lod_vox_block(renderDistance->value);
            set_voxel_node_lods(world, voxelNode, vox_lod);
            continue;
        }*/
            /*const ecs_entity_t e3 = get_node_entity_VoxelNode(node);
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
                            if (zox_has(e3, ChunkMeshDirty)) {
                                zox_set(e3, ChunkMeshDirty, { chunk_dirty_state_trigger })
                            }
                        }
                    }
                }
            }*/
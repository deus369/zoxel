#define zox_disable_block_spawns_hash
// todo: don't use any constants here for numbers
// todo: use voxel scale passed in
// extern unsigned char get_block_voxes_lod_from_camera_distance(unsigned char distance_to_camera);

// keeps track of the node, position, depth as we dig
typedef struct {
    ChunkOctree *chunk; // const
    int3 octree_position;
    unsigned char depth;
} NodeDelveData;

typedef struct {
    const ecs_entity_t *blocks;
    const ecs_entity_t *block_voxes;
    const unsigned char *block_vox_offsets;
    const unsigned char block_voxes_count;
    const float3 chunk_position_real;
#ifndef zox_disable_block_spawns_hash
    // BlockSpawns *block_spawns;
#endif
    SpawnBlockVox *spawn_data;
} UpdateBlockEntities;

// assumes this is max depth voxel
void remove_old_voxel_by_link(ecs_world_t *world, ChunkOctree *chunk) {
    if (!chunk->nodes) return;
    const ecs_entity_t e3 = ((VoxelEntityLink*)chunk->nodes)->value;
    if (zox_valid(e3)) {
        // zox_log(" - deleting previous block vox [%lu]\n", previous_e)
        zox_delete(e3)
        free(chunk->nodes);
        chunk->nodes = NULL;
    }
}

/* void remove_old_block_vox_from_tree(ecs_world_t *world, BlockSpawns *block_spawns, const int3 octree_position) {
#ifdef zox_disable_block_spawns_hash
    return;
#endif
    byte3 position_local = int3_to_byte3(octree_position);
    if (byte3_hashmap_has(block_spawns->value, position_local)) {
        // zox_log(" > destroying vox block [%ix%ix%i]\n", position_local.x, position_local.y, position_local.z)
        const ecs_entity_t old_vox_block = byte3_hashmap_get(block_spawns->value, position_local);
        if (old_vox_block) zox_delete(old_vox_block)
            byte3_hashmap_remove(block_spawns->value, position_local);
    }
} */

void delete_block_entities(ecs_world_t *world, ChunkOctree *chunk, const unsigned char max_depth, unsigned char depth) {
    if (depth == max_depth) {
        remove_old_voxel_by_link(world, chunk);
    } else if (chunk->nodes) {
        depth++;
        for (unsigned char i = 0; i < octree_length; i++) {
            delete_block_entities(world, &chunk->nodes[i], max_depth, depth);
        }
    }
}

// first check if exists, if it does check if voxel type differs, for removing/adding
// goes through nodes, if not in hashmap, it  will spawn anew
void update_block_entities(ecs_world_t *world, const UpdateBlockEntities *data, NodeDelveData *delve_data) {
    if (delve_data->depth == max_octree_depth) {
        // if null or air, remove
        if (!delve_data->chunk || !delve_data->chunk->value) {
#ifndef zox_disable_block_spawns_hash
            remove_old_block_vox_from_tree(world, data->block_spawns, delve_data->octree_position);
#else
            remove_old_voxel_by_link(world, delve_data->chunk);
#endif
            return; // air returns!
        }
        // cheeck if out of bounds
        const unsigned char block_index = delve_data->chunk->value - 1;
        if (block_index >= data->block_voxes_count) {
            zox_log(" ! block_index out of bounds %i of %i\n", block_index, data->block_voxes_count)
            return;
        }
        const ecs_entity_t block_meta = data->blocks[block_index];
        const unsigned char is_world_block = zox_has(block_meta, BlockPrefabLink);
        // cheeck if vox model
        //  if meta data is block vox type, spawn, otherwise, remove
        if (!is_world_block && !data->block_voxes[block_index]) {
#ifndef zox_disable_block_spawns_hash
            remove_old_block_vox_from_tree(world, data->block_spawns, delve_data->octree_position);
#else
            remove_old_voxel_by_link(world, delve_data->chunk);
#endif
            return;
        }
        // + spawn block vox
        const float voxel_scale = 0.5f; // terrain scale
        data->spawn_data->position_local = int3_to_byte3(delve_data->octree_position);
#ifndef zox_disable_block_spawns_hash
        if (byte3_hashmap_has(data->block_spawns->value, data->spawn_data->position_local)) return;
#else
        // if exists already, shouldn't we check if is the same block vox type?
        // if exists, and is same type, return!
        ChunkOctree *chunk = delve_data->chunk;
        if (chunk->nodes) {
            const ecs_entity_t e3 = ((VoxelEntityLink*)chunk->nodes)->value;
            if (zox_valid(e3) && zox_has(e3, BlockIndex)) {
                const unsigned char old_block_index = zox_get_value(e3, BlockIndex)
                if (old_block_index == block_index) {
                    // zox_log(" > trying to spawn same block vox [%i]\n", old_block_index)
                    // Updates RenderLod of previous Vox Blocks
                    const unsigned char vox_lod = data->spawn_data->render_lod;
                    const unsigned char vox_lod_old = zox_get_value(e3, RenderLod)
                    if (vox_lod_old != vox_lod) {
                        zox_set(e3, RenderLod, { vox_lod })
                        zox_set(e3, ChunkDirty, { chunk_dirty_state_lod_updated })
                    }
                    return;
                }
            }
        }
#endif
        // if not same time, spawn new here
        data->spawn_data->block_index = block_index;
        data->spawn_data->vox = data->block_voxes[block_index];
        float3 position_real = float3_from_int3(delve_data->octree_position);
        float3_multiply_float_p(&position_real, voxel_scale);
        float3_add_float3_p(&position_real, data->chunk_position_real);
        float3_add_float3_p(&position_real, (float3) { -voxel_scale * 0.5f, -voxel_scale * 0.5f, -voxel_scale * 0.5f });
        if (data->block_vox_offsets[block_index]) float3_add_float3_p(&position_real, (float3) { 0, -0.125f, 0 });
        data->spawn_data->position_real = position_real;
        // todo: instead of hash, replace OctreeNode with OctreeNodeEntity - link directly in the node
        ecs_entity_t e2;
        if (is_world_block) {
            const ecs_entity_t block_prefab = zox_get_value(block_meta, BlockPrefabLink)
            e2 = zox_instancee(block_prefab)
            zox_log("block world entity spawning: %lu from %lu\n", e2, block_prefab)
        } else {
            e2 = spawn_block_vox(world, data->spawn_data);
        }
#ifndef zox_disable_block_spawns_hash
        byte3_hashmap_add(data->block_spawns->value, data->spawn_data->position_local, e2);
#else
        remove_old_voxel_by_link(world, delve_data->chunk);
        chunk->nodes = malloc(sizeof(VoxelEntityLink));
        if (!chunk->nodes) {
            zox_log(" ! failed to allocate nodes\n")
            zox_delete(e2)
            return;
        }
        *(VoxelEntityLink*)chunk->nodes = (VoxelEntityLink){ .value = e2 };
#endif
        // zox_log(" + spawned vox model: depth %i - scale %f - %ix%ix%i - r [%fx%fx%f] - [%i]\n", depth, voxel_scale, octree_position.x, octree_position.y, octree_position.z, position_real.x, position_real.y, position_real.z, count_byte3_hashmap(block_spawns->value))
    } else {
        NodeDelveData delve_data2 = {
            .chunk = NULL,
            .depth = delve_data->depth + 1
        };
        int3 octree_position = delve_data->octree_position;
        int3_multiply_int_p(&octree_position, 2);
        if (delve_data->chunk && delve_data->chunk->nodes) {
            for (unsigned char i = 0; i < octree_length; i++) {
                delve_data2.chunk = &delve_data->chunk->nodes[i];
                delve_data2.octree_position = int3_add(octree_position, octree_positions[i]);
                update_block_entities(world, data, &delve_data2);
            }
        } else {
#ifndef zox_disable_block_spawns_hash
            // traverse down with null nodes, making sure to clean up vox spawns on closed nodes
            for (unsigned char i = 0; i < octree_length; i++) {
                delve_data2.octree_position = int3_add(octree_position, octree_positions[i]);
                update_block_entities(world, data, &delve_data2);
            }
#endif
        }
    }
}

// updates during ChunkLodDirty and ChunkDirty events
void update_block_voxes(ecs_world_t *world, const VoxLink *voxLink, const ChunkPosition *chunkPosition, const unsigned char vox_lod, const RenderDisabled *renderDisabled, ChunkOctree *chunk) {
    const ecs_entity_t realm = zox_get_value(voxLink->value, RealmLink)
    const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
    const unsigned char block_voxes_count = voxelLinks->length;
    ecs_entity_t blocks[block_voxes_count];
    ecs_entity_t block_voxes[block_voxes_count];
    unsigned char block_vox_offsets[block_voxes_count];
    memset(block_voxes, 0, block_voxes_count * sizeof(ecs_entity_t));
    memset(block_vox_offsets, 0, block_voxes_count);
    for (int j = 0; j < block_voxes_count; j++) {
        const ecs_entity_t block = voxelLinks->value[j];
        blocks[j] = block;
        if (zox_gett_value(block, BlockModel) == zox_block_vox) {
            block_voxes[j] = zox_get_value(block, ModelLink)
            if (zox_has(block, BlockVoxOffset)) block_vox_offsets[j] = zox_get_value(block, BlockVoxOffset)
        }
    }
    // convert chunk position to real
    // const float3 chunk_position_real = zox_get_value(chunk, Position3D)
    const float3 chunk_position_real = float3_add(float3_half, float3_multiply_float(int3_to_float3(chunkPosition->value), 16.0f)); // calculate
    SpawnBlockVox spawn_data = {
        .prefab = prefab_block_vox,
        .render_lod = vox_lod,
        .render_disabled = renderDisabled->value // until i get frustum to cull these
    };
#ifndef zox_disable_block_spawns_hash
    if (!block_spawns->value) block_spawns->value = create_byte3_hashmap(max_vox_blocks);
    if (!block_spawns->value) {
        zox_log(" ! error creating block spawns hashmap\n")
        return;
    }
#endif
    UpdateBlockEntities data = {
        .blocks = blocks,
        .block_voxes = block_voxes,
        .block_vox_offsets = block_vox_offsets,
        .block_voxes_count = block_voxes_count,
        .chunk_position_real = chunk_position_real,
        // .block_spawns = block_spawns,
        .spawn_data = &spawn_data,
    };
    NodeDelveData delve_data = {
        .chunk = chunk
    };
    update_block_entities(world, &data, &delve_data);
    // spawn_block_vox_in_tree(world, chunkOctree, block_spawns, &spawn_data, chunk_position_real, int3_zero, 0, block_voxes, block_vox_offsets, block_voxes_count);
}


// temp way to split up function
/*void update_block_voxes_on_node(ecs_world_t *world, const VoxLink *voxLink, const ChunkPosition *chunkPosition, const unsigned char vox_lod, const RenderDisabled *renderDisabled, const ChunkOctree *chunk, BlockSpawns *block_spawns, const unsigned char node_index) {
    const ecs_entity_t realm = zox_get_value(voxLink->value, RealmLink)
    const VoxelLinks *voxelLinks = zox_get(realm, VoxelLinks)
    const unsigned char block_voxes_count = voxelLinks->length;
    ecs_entity_t block_voxes[block_voxes_count];
    unsigned char block_vox_offsets[block_voxes_count];
    memset(block_voxes, 0, block_voxes_count * sizeof(ecs_entity_t));
    memset(block_vox_offsets, 0, block_voxes_count);
    for (int j = 0; j < block_voxes_count; j++) {
        const ecs_entity_t block = voxelLinks->value[j];
        if (zox_gett_value(block, BlockModel) == zox_block_vox) {
            block_voxes[j] = zox_get_value(block, ModelLink)
            if (zox_has(block, BlockVoxOffset)) block_vox_offsets[j] = zox_get_value(block, BlockVoxOffset)
        }
    }
    // convert chunk position to real
    // const float3 chunk_position_real = zox_get_value(chunk, Position3D)
    const float3 chunk_position_real = float3_add(float3_half, float3_multiply_float(int3_to_float3(chunkPosition->value), 16.0f)); // calculate
    SpawnBlockVox spawn_data = {
        .prefab = prefab_block_vox,
        .render_lod = vox_lod,
        .render_disabled = renderDisabled->value // until i get frustum to cull these
    };
    if (!block_spawns->value) block_spawns->value = create_byte3_hashmap(max_vox_blocks);
    if (!block_spawns->value) {
        zox_log(" ! error creating block spawns hashmap\n")
        return;
    }
    const int3 child_octree_position = octree_positions[node_index];
    ChunkOctree *child_node = NULL;
    if (chunk && chunk->nodes) child_node = &chunk->nodes[node_index];
    spawn_block_vox_in_tree(world, child_node, block_spawns, &spawn_data, chunk_position_real, child_octree_position, 1, block_voxes, block_vox_offsets, block_voxes_count);
}*/



/*void spawn_block_vox_in_tree(ecs_world_t *world, const ChunkOctree *octree, BlockSpawns *block_spawns, SpawnBlockVox *spawn_data, const float3 chunk_position_real, int3 octree_position, const unsigned char depth, const ecs_entity_t block_voxes[], const unsigned char block_vox_offsets[], const unsigned char block_voxes_count) {
 *    if (depth == max_octree_depth) {
 *        // if null or air, remove
 *        if (!octree || !octree->value) {
 *            remove_old_block_vox_from_tree(world, block_spawns, octree_position);
 *            return; // air returns!
 *        }
 *        // cheeck if vox model
 *        const unsigned char block_index = octree->value - 1;
 *        if (block_index >= block_voxes_count) {
 *            zox_log(" ! block_index out of bounds %i of %i\n", block_index, block_voxes_count)
 *            return;
 *        }
 *        //  if meta data is block vox type, spawn, otherwise, remove
 *        if (!block_voxes[block_index]) {
 *            remove_old_block_vox_from_tree(world, block_spawns, octree_position);
 *        } else {
 *            // + spawn block vox
 *            const float voxel_scale = 0.5f; // terrain scale
 *            spawn_data->position_local = int3_to_byte3(octree_position);
 *            // if (byte3_hashmap_has(block_spawns->value, spawn_data->position_local)) return;
 *            spawn_data->vox = block_voxes[block_index];
 *            float3 position_real = float3_from_int3(octree_position);
 *            float3_multiply_float_p(&position_real, voxel_scale);
 *            float3_add_float3_p(&position_real, chunk_position_real);
 *            float3_add_float3_p(&position_real, (float3) { -voxel_scale * 0.5f, -voxel_scale * 0.5f, -voxel_scale * 0.5f });
 *            if (block_vox_offsets[block_index]) float3_add_float3_p(&position_real, (float3) { 0, -0.125f, 0 });
 *            spawn_data->position_real = position_real;
 *            // todo: instead of hash, replace OctreeNode with OctreeNodeEntity - link directly in the node
 *            // const ecs_entity_t e2 = spawn_block_vox(world, spawn_data);
 *            // byte3_hashmap_add(block_spawns->value, spawn_data->position_local, e2);
 *
 *            // zox_log(" + spawned vox model: depth %i - scale %f - %ix%ix%i - r [%fx%fx%f] - [%i]\n", depth, voxel_scale, octree_position.x, octree_position.y, octree_position.z, position_real.x, position_real.y, position_real.z, count_byte3_hashmap(block_spawns->value))
 *        }
 *    } else {
 *        int3_multiply_int_p(&octree_position, 2);
 *        const unsigned char new_depth = depth + 1;
 *        if (octree && octree->nodes) {
 *            for (int i = 0; i < octree_length; i++) {
 *                int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
 *                spawn_block_vox_in_tree(world, &octree->nodes[i], block_spawns, spawn_data, chunk_position_real, child_octree_position, new_depth, block_voxes, block_vox_offsets, block_voxes_count);
 *            }
 *        } else {
 *            // traverse down with null nodes, making sure to clean up vox spawns on closed nodes
 *            for (int i = 0; i < octree_length; i++) {
 *                int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
 *                spawn_block_vox_in_tree(world, NULL, block_spawns, spawn_data, chunk_position_real, child_octree_position, new_depth, block_voxes, block_vox_offsets, block_voxes_count);
 *            }
 *        }
 *    }
 * }*/


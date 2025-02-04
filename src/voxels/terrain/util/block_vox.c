#define zox_disable_block_spawns_hash
// todo: don't use any constants here for numbers
// todo: use voxel scale passed in

// keeps track of the node, position, depth as we dig
typedef struct {
    ChunkOctree *chunk; // const
    int3 octree_position;
    unsigned char depth;
    const unsigned char max_depth;
} NodeDelveData;

typedef struct {
    const ecs_entity_t chunk;
    const ecs_entity_t *blocks;
    const ecs_entity_t *block_voxes;
    const ecs_entity_t *block_prefabs;
    const unsigned char *block_vox_offsets;
    const unsigned char block_voxes_count;
    const float3 chunk_position_real;
    SpawnBlockVox *spawn_data;
} UpdateBlockEntities;

// used within cleanup code
void delete_vox_entity_from_nodes(ecs_world_t *world, ChunkOctree *chunk) {
    const ecs_entity_t e3 = ((VoxelEntityLink*)chunk->nodes)->value;
    if (zox_valid(e3)) {
        zox_delete(e3)
    }
}

// returns 1 if needs allocate a new VoxelEntityLink
unsigned char delete_old_voxel_by_link(ecs_world_t *world, ChunkOctree *chunk) {
    if (!chunk->nodes) return 1;
    const ecs_entity_t e3 = ((VoxelEntityLink*)chunk->nodes)->value;
    if (zox_valid(e3)) {
        zox_delete(e3)
    } else {
        zox_log(" !!! error delete_old_voxel_by_link : minivox voxel link\n")
    }
    return 0;
}

// assumes this is max depth voxel
void remove_old_voxel_by_link(ecs_world_t *world, ChunkOctree *chunk) {
    if (!chunk->nodes) return;
    const ecs_entity_t e3 = ((VoxelEntityLink*)chunk->nodes)->value;
    if (zox_valid(e3)) {
        zox_delete(e3)
        free(chunk->nodes);
        chunk->nodes = NULL;
    } else {
        zox_log(" !!! error remove_old_voxel_by_link : minivox voxel link\n")
    }
}

void delete_block_entities(ecs_world_t *world, ChunkOctree *chunk,  unsigned char depth, const unsigned char max_depth) {
    if (depth == max_depth) {
        remove_old_voxel_by_link(world, chunk);
    } else if (chunk->nodes) {
        depth++;
        for (unsigned char i = 0; i < octree_length; i++) {
            delete_block_entities(world, &chunk->nodes[i], depth, max_depth);
        }
    }
}

// first check if exists, if it does check if voxel type differs, for removing/adding
// goes through nodes, if not in hashmap, it  will spawn anew
void update_block_entities(ecs_world_t *world, const UpdateBlockEntities *data, NodeDelveData *delve_data) {
    const float voxel_scale = 0.5f; // terrain scale
    if (delve_data->depth == delve_data->max_depth) {
        // if null or air, remove
        if (!delve_data->chunk || !delve_data->chunk->value) {
            remove_old_voxel_by_link(world, delve_data->chunk);
            return; // air returns!
        }
        // cheeck if out of bounds
        const unsigned char block_index = delve_data->chunk->value - 1;
        if (block_index >= data->block_voxes_count) {
            zox_log(" ! block_index out of bounds %i of %i\n", block_index, data->block_voxes_count)
            return;
        }
        const ecs_entity_t block_prefab = data->block_prefabs[block_index];
        // zox_has(block_meta, BlockPrefabLink);
        // cheeck if vox model - if meta data is block vox type, spawn, otherwise, remove
        if (!block_prefab) {
            remove_old_voxel_by_link(world, delve_data->chunk);
            return;
        }
        // + spawn block vox
        data->spawn_data->position_local = int3_to_byte3(delve_data->octree_position);
        // if exists already, shouldn't we check if is the same block vox type?
        // if exists, and is same type, return!
        ChunkOctree *chunk = delve_data->chunk;
        if (chunk->nodes) {
            const ecs_entity_t e3 = ((VoxelEntityLink*) chunk->nodes)->value;
            if (zox_valid(e3)) {
                // this means e3 has spawned
                // we should check its the same one
                // we can add lod to mechanical entities too
                if (zox_has(e3, BlockIndex)) {
                    const unsigned char old_block_index = zox_get_value(e3, BlockIndex)
                    if (old_block_index == block_index) {
                        // zox_log(" > trying to spawn same block vox [%i]\n", old_block_index)
                        // Updates RenderLod of previous Vox Blocks
                        const unsigned char vox_lod = data->spawn_data->render_lod;
                        const unsigned char vox_lod_old = zox_get_value(e3, RenderLod)
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
        float3_add_float3_p(&position_real, (float3) { -voxel_scale * 0.5f, -voxel_scale * 0.5f, -voxel_scale * 0.5f });
        if (data->block_vox_offsets[block_index]) float3_add_float3_p(&position_real, (float3) { 0, -0.125f, 0 });
        data->spawn_data->position_real = position_real;
        // todo: instead of hash, replace OctreeNode with OctreeNodeEntity - link directly in the node
        ecs_entity_t e2;
        // const unsigned char is_world_block = block_prefab && !zox_has(block_prefab, BlockVox);
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
            // zox_set(e2, Position3D, { position_real })
        }
        if (delete_old_voxel_by_link(world, delve_data->chunk)) {
            chunk->nodes = malloc(sizeof(VoxelEntityLink));
        }
        if (!chunk->nodes) {
            zox_log(" ! failed to allocate nodes\n")
            zox_delete(e2)
            return;
        }
        *(VoxelEntityLink*) chunk->nodes = (VoxelEntityLink){ .value = e2 };
        // remove_old_voxel_by_link(world, chunk);
        // zox_log(" + spawned vox model: depth %i - scale %f - %ix%ix%i - r [%fx%fx%f] - [%i]\n", depth, voxel_scale, octree_position.x, octree_position.y, octree_position.z, position_real.x, position_real.y, position_real.z, count_byte3_hashmap(block_spawns->value))
    } else {
        int3 octree_position = delve_data->octree_position;
        int3_multiply_int_p(&octree_position, 2);
        if (delve_data->chunk && delve_data->chunk->nodes) {
            for (unsigned char i = 0; i < octree_length; i++) {
                NodeDelveData delve_data_child = {
                    .chunk = &delve_data->chunk->nodes[i],
                    .octree_position = int3_add(octree_position, octree_positions[i]),
                    .depth = delve_data->depth + 1,
                    .max_depth = delve_data->max_depth
                };
                update_block_entities(world, data, &delve_data_child);
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

// updates during ChunkLodDirty and ChunkMeshDirty events
void update_block_voxes(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t terrain, const ChunkPosition *chunkPosition, const unsigned char vox_lod, const RenderDisabled *renderDisabled, ChunkOctree *chunk, const unsigned char max_depth) {
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    const unsigned char block_voxes_count = voxels->length;
    if (block_voxes_count == 0) {
        return;
    }
    ecs_entity_t blocks[block_voxes_count];
    ecs_entity_t block_voxes[block_voxes_count];
    ecs_entity_t block_prefabs[block_voxes_count];
    unsigned char block_vox_offsets[block_voxes_count];
    zero_memory(block_voxes, block_voxes_count, ecs_entity_t)
    zero_memory(block_prefabs, block_voxes_count, ecs_entity_t)
    zero_memory(block_vox_offsets, block_voxes_count, unsigned char)
    //memset(block_voxes, 0, block_voxes_count * sizeof(ecs_entity_t));
    //memset(block_prefabs, 0, block_voxes_count * sizeof(ecs_entity_t));
    //memset(block_vox_offsets, 0, block_voxes_count);
    for (int j = 0; j < block_voxes_count; j++) {
        const ecs_entity_t block_meta = voxels->value[j];
        blocks[j] = block_meta;
        if (zox_gett_value(block_meta, BlockModel) == zox_block_vox) {
            block_voxes[j] = zox_get_value(block_meta, ModelLink)
            if (zox_has(block_meta, BlockVoxOffset)) block_vox_offsets[j] = zox_get_value(block_meta, BlockVoxOffset)
        }
        if (zox_has(block_meta, BlockPrefabLink)) {
            block_prefabs[j] = zox_get_value(block_meta, BlockPrefabLink)
        }
    }
    // convert chunk position to real
    const float3 chunk_position_real = float3_add(float3_half, float3_multiply_float(int3_to_float3(chunkPosition->value), 16.0f)); // calculate
    SpawnBlockVox spawn_data = {
        .prefab = prefab_block_vox,
        .render_lod = vox_lod,
        .render_disabled = renderDisabled->value // until i get frustum to cull these
    };
    UpdateBlockEntities data = {
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

// int spawned_block_voxes = 0;
extern unsigned char get_voxes_lod_from_camera_distance(unsigned char distance_to_camera);

// first check if exists, if it does check if voxel type differs, for removing/adding
// goes through nodes, if not in hashmap, it  will spawn anew
void spawn_block_vox_in_tree(const ChunkOctree *octree, BlockSpawns *block_spawns, SpawnBlockVox *spawn_data, const float3 chunk_position_real, int3 octree_position, unsigned char depth, const ecs_entity_t block_voxes[], const unsigned char block_vox_offsets[], const unsigned char block_voxes_count) {
    if (depth == max_octree_depth) {
        if (octree == NULL || octree->value == 0) {
            byte3 position_local = int3_to_byte3(octree_position);
            if (byte3_hashmap_has(block_spawns->value, position_local)) {
                // zox_log(" > destroying vox block [%ix%ix%i]\n", position_local.x, position_local.y, position_local.z)
                const ecs_entity_t old_vox_block = byte3_hashmap_get(block_spawns->value, position_local);
                if (old_vox_block) zox_delete(old_vox_block)
                byte3_hashmap_remove(block_spawns->value, position_local);
            }
            return; // air returns!
        }
        // cheeck if vox model
        const unsigned char block_index = octree->value - 1;
        if (block_index >= block_voxes_count) {
            zox_log(" ! block_index out of bounds %i of %i\n", block_index, block_voxes_count)
            return;
        }
        if (block_voxes[block_index]) { // only for block vox models
            const float voxel_scale = 0.5f; // terrain scale
            /*if (octree->value != zox_block_grass_vox) return; // only spawn for grass_vox atm */
            // if (count_byte3_hashmap(block_spawns->value) == max_vox_blocks) return; // max
            spawn_data->position_local = int3_to_byte3(octree_position);
            if (byte3_hashmap_has(block_spawns->value, spawn_data->position_local)) return;
            spawn_data->vox = block_voxes[block_index];
            // ChunkScale (0.5f) * ChunkSize (16)
            // 0.5f *
            // const float voxel_scale = (1.0f / 32.0f); //  octree_scales2[depth] * 0.5f * 16.0f; // todo: use voxel scale passed in
            float3 position_real = float3_from_int3(octree_position);
            float3_multiply_float_p(&position_real, voxel_scale);
            float3_add_float3_p(&position_real, chunk_position_real);
            // 0.5f * ChunkScale - which is 0.5f = 0.25f
            float3_add_float3_p(&position_real, (float3) { -voxel_scale * 0.5f, -voxel_scale * 0.5f, -voxel_scale * 0.5f });
            // float3_add_float3_p(&position_real, (float3) { - 1.0f / 64.0f, - 1.0f / 64.0f, - 1.0f / 64.0f });
            if (block_vox_offsets[block_index]) float3_add_float3_p(&position_real, (float3) { 0, -0.125f, 0 });
            spawn_data->position_real = position_real;
            // spawn our block voxes
            const ecs_entity_t e2 = spawn_block_vox(world, spawn_data);
            byte3_hashmap_add(block_spawns->value, spawn_data->position_local, e2);
            // zox_log(" + spawned vox model: depth %i - scale %f - %ix%ix%i - r [%fx%fx%f] - [%i]\n", depth, voxel_scale, octree_position.x, octree_position.y, octree_position.z, position_real.x, position_real.y, position_real.z, count_byte3_hashmap(block_spawns->value))
            // spawned_block_voxes++;
        } else {
            byte3 position_local = int3_to_byte3(octree_position);
            if (byte3_hashmap_has(block_spawns->value, position_local)) {
                // zox_log(" > destroying vox block [%ix%ix%i]\n", position_local.x, position_local.y, position_local.z)
                const ecs_entity_t old_vox_block = byte3_hashmap_get(block_spawns->value, position_local);
                if (old_vox_block) zox_delete(old_vox_block)
                byte3_hashmap_remove(block_spawns->value, position_local);
            }
        }
    } else if (octree && octree->nodes) {
        int3_multiply_int_p(&octree_position, 2);
        const unsigned char new_depth = depth + 1;
        for (int i = 0; i < octree_length; i++) {
            int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
            spawn_block_vox_in_tree(&octree->nodes[i], block_spawns, spawn_data, chunk_position_real, child_octree_position, new_depth, block_voxes, block_vox_offsets, block_voxes_count);
        }
    } else {
        // traverse down with null nodes, making sure to clean up vox spawns on closed nodes
        int3_multiply_int_p(&octree_position, 2);
        const unsigned char new_depth = depth + 1;
        for (int i = 0; i < octree_length; i++) {
            int3 child_octree_position = int3_add(octree_position, octree_positions[i]);
            spawn_block_vox_in_tree(NULL, block_spawns, spawn_data, chunk_position_real, child_octree_position, new_depth, block_voxes, block_vox_offsets, block_voxes_count);
        }
    }
}

// updates during ChunkLodDirty and ChunkDirty events
void update_block_voxes(ecs_world_t *world, const VoxLink *voxLink, const ChunkPosition *chunkPosition, const RenderLod *renderLod, const RenderDisabled *renderDisabled, const ChunkOctree *chunkOctree, BlockSpawns *blockSpawns) {
    const unsigned char camera_distance = renderLod->value;
    const unsigned char vox_lod = get_voxes_lod_from_camera_distance(camera_distance);
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
    float3 chunk_position_real = float3_add(float3_half, float3_multiply_float(int3_to_float3(chunkPosition->value), 16.0f)); // calculate
    SpawnBlockVox spawn_data = {
        .prefab = prefab_block_vox,
        .render_lod = vox_lod,
        .render_disabled = renderDisabled->value // until i get frustum to cull these
    };
    if (!blockSpawns->value) {
        blockSpawns->value = create_byte3_hashmap(max_vox_blocks);
    }
    if (blockSpawns->value) {
        spawn_block_vox_in_tree(chunkOctree, blockSpawns, &spawn_data, chunk_position_real, int3_zero, 0, block_voxes, block_vox_offsets, block_voxes_count);
    }
}


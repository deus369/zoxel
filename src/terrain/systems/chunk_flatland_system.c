// generates our terrain voxels
void ChunkFlatlandSystem(ecs_iter_t *it) {
    uint update_count = 0;
    const byte target_depth = terrain_depth;
    const byte chunk_voxel_length = powers_of_two_byte[target_depth];
    zox_field_world()
    zox_field_in(ChunkPosition, chunkPositions, 2)
    zox_field_out(GenerateChunk, generateChunks, 3)
    zox_field_out(ChunkOctree, chunkOctrees, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateChunk, generateChunks, generateChunk)
        if (generateChunk->value != chunk_generate_state_update) {
            continue;
        }
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        const SetVoxelTargetData datam_dirt = { .depth = target_depth, .voxel = zox_block_dirt, .effect_nodes = 1 };
        const SetVoxelTargetData datam_grass = { .depth = target_depth, .voxel = zox_block_grass, .effect_nodes = 1 };
        SetVoxelData data = { .node = chunkOctree };
        byte3 voxel_position;
        chunkOctree->linked = target_depth;
        fill_new_octree(chunkOctree, 0, target_depth);
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                const int global_height = int_floor(terrain_amplifier * flat_height_level);
                const int local_height_raw = global_height - chunk_position_y;
                const int local_height = int_min(chunk_voxel_length - 1, local_height_raw);
                if (local_height >= 0) {
                    for (voxel_position.y = 0; voxel_position.y <= local_height; voxel_position.y++) {
                        data.position = voxel_position;
                        if (voxel_position.y  == local_height_raw) {
                            set_voxel(&datam_grass, data);
                        } else {
                            set_voxel(&datam_dirt, data);
                        }
                    }
                }
            }
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(world, chunkOctree, target_depth, 0);
#endif
        update_count++;
    }
    if (update_count > 0 && zox_log_terrain_generation) {
        zox_log(" - [%i] flat [%i]", ecs_run_count, update_count)
    }
} zox_declare_system(ChunkFlatlandSystem)

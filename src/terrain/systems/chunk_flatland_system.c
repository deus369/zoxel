// generates our terrain voxels
void ChunkFlatlandSystem(ecs_iter_t *it) {
    const byte target_depth = terrain_depth;
    const byte chunk_voxel_length = powers_of_two_byte[target_depth];
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkPosition)
    zox_sys_out(GenerateChunk)
    zox_sys_out(VoxelNode)
    zox_sys_out(NodeDepth)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(NodeDepth, nodeDepth)
        zox_sys_o(GenerateChunk, generateChunk)
        if (generateChunk->value != chunk_generate_state_update) {
            continue;
        }
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        const SetVoxelTargetData datam_dirt = {
            .depth = target_depth,
            .voxel = zox_block_dirt,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_grass = {
            .depth = target_depth,
            .voxel = zox_block_grass,
            .effect_nodes = 1
        };
        SetVoxelData data = {
            .node = voxelNode
        };
        byte3 voxel_position;
        nodeDepth->value = target_depth;
        if (chunk_position_y < 0) {
            fill_new_octree(voxelNode, zox_block_dirt, 0);
        } else {
            fill_new_octree(voxelNode, 0, 0);
        }
        /*for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                const int global_height = int_floorf(terrain_amplifier * flat_height_level);
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
        cleanup_nodes(world, voxelNode);*/
    }
} zox_declare_system(ChunkFlatlandSystem)

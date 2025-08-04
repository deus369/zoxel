// generates our terrain voxels
void ChunkFlatlandSystem(ecs_iter_t *it) {
    const byte target_depth = terrain_depth;
    const byte chunk_voxel_length = powers_of_two_byte[target_depth];
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
        // byte3 voxel_position;
        nodeDepth->value = target_depth;
        if (chunk_position_y < 0) {
            fill_new_octree(voxelNode, zox_block_dirt, 0);
        } else {
            fill_new_octree(voxelNode, 0, 0);
        }
    }
} zox_declare_system(ChunkFlatlandSystem)

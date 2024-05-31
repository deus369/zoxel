// generates our terrain voxels
void ChunkFlatlandSystem(ecs_iter_t *it) {
    const unsigned char target_depth = max_octree_depth;
    const unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
    zox_field_in(ChunkPosition, chunkPositions, 2)
    zox_field_out(GenerateChunk, generateChunks, 3)
    zox_field_out(ChunkDirty, chunkDirtys, 4)
    zox_field_out(ChunkOctree, chunkOctrees, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateChunk, generateChunks, generateChunk)
        if (generateChunk->value != 1) continue;
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value) continue;
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        fill_new_octree(chunkOctree, 0, target_depth);
        const SetVoxelTargetData datam = { .depth = target_depth, .voxel = 1, .effect_nodes = 1 };
        SetVoxelData data = { .node = chunkOctree };
        byte3 voxel_position;
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                int global_height = int_floor(terrain_amplifier * flat_height_level);
                int local_height = int_min(chunk_voxel_length, global_height - chunk_position_y);
                if (local_height < 0) local_height = 0;
                // else if (local_height > chunk_voxel_length) local_height = chunk_voxel_length; // limit
                for (voxel_position.y = 0; voxel_position.y < local_height; voxel_position.y++) {
                    data.position = voxel_position;
                    set_voxel(&datam, data);
                }
            }
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(chunkOctree);
#endif
        // close_solid_nodes(chunkOctree);
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }
} zox_declare_system(ChunkFlatlandSystem)

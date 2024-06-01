byte3 find_position_in_chunk(const ChunkOctree *chunk_octree, const unsigned char target_depth) {
    if (chunk_octree == NULL) return byte3_full;
    const unsigned char max_checks = 32;
    const unsigned char chunk_length = powers_of_two_byte[target_depth];
    unsigned char checks_count = 0;
    while (checks_count < max_checks) {
        byte3 local_position = (byte3) { rand() % chunk_length, chunk_length - 1, rand() % chunk_length };
        byte3 temp = local_position;
        unsigned char voxel = get_octree_voxel(chunk_octree, &temp, target_depth);
        if (voxel == 0) {
            // find ground now
            for (local_position.y = chunk_length - 2; local_position.y >= 0; local_position.y--) {
                temp = local_position;
                voxel = get_octree_voxel(chunk_octree, &temp, target_depth);
                if (voxel != 0) {
                    local_position.y++; // place on top of solid
                    return local_position;
                }
                if (local_position.y == 0) break; // since byte cannot go under 0
            }
        }
        checks_count++;
    }
    return byte3_full;
}

float3 local_to_real_position_character(const byte3 local_position, const int3 chunk_voxel_position) {
    const int3 global_voxel_position = int3_add(chunk_voxel_position, byte3_to_int3(local_position));
    float3 position = int3_to_float3(global_voxel_position);
    float3_multiply_float_p(&position, terrain_voxel_scale);
    position.y += 0.26f; // 0.75f;
    position.y += 0.01f; // extra
    return position;
}

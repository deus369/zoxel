byte3 find_position_in_chunk(const ChunkOctree *chunk_octree, const unsigned char target_depth) {
    if (chunk_octree == NULL) return byte3_full;
    const unsigned char chunk_length = powers_of_two_byte[target_depth];
    const unsigned char max_checks = 32;
    unsigned char checks_count = 0;
    while (checks_count < max_checks) {
        // get a random x-z position
        byte3 local_position = (byte3) { rand() % chunk_length, chunk_length - 1, rand() % chunk_length };
        // zox_log("   > checking position: %ix%i\n", local_position.x, local_position.z)
        byte3 temp2 = local_position;
        const unsigned char voxel1 = get_octree_voxel(chunk_octree, &temp2, target_depth);
        if (!voxel1) {
            // find ground now
            for (local_position.y = chunk_length - 2; local_position.y >= 0; local_position.y--) {
                byte3 temp = local_position;
                const unsigned char voxel = get_octree_voxel(chunk_octree, &temp, target_depth);
                if (voxel) { // can stand on voxel
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


byte3 find_position_in_chunk_with_above(const ChunkOctree *chunk_octree, const unsigned char target_depth, const ChunkOctree *chunk_octree_above) {
    if (chunk_octree == NULL) return byte3_full;
    const unsigned char chunk_length = powers_of_two_byte[target_depth];
    const unsigned char max_checks = 32;
    unsigned char checks_count = 0;
    while (checks_count < max_checks && chunk_octree_above) {
        // get a random x-z position
        byte3 local_position = (byte3) { rand() % chunk_length, 0, rand() % chunk_length };
        // zox_log("   > checking position: %ix%i\n", local_position.x, local_position.z)
        byte3 temp2 = local_position;
        const unsigned char voxel1 = get_octree_voxel(chunk_octree_above, &temp2, target_depth);
        if (!voxel1) {
            // find ground now
            for (local_position.y = chunk_length - 1; local_position.y >= 0; local_position.y--) {
                byte3 temp = local_position;
                const unsigned char voxel = get_octree_voxel(chunk_octree, &temp, target_depth);
                if (voxel) { // can stand on voxel
                    local_position.y++; // place on top of solid
                    return local_position;
                }
                if (local_position.y == 0) break; // since byte cannot go under 0
            }
        }
        checks_count++;
    }
    return find_position_in_chunk(chunk_octree, target_depth);
}

float3 local_to_real_position_character(const byte3 local_position, const int3 chunk_voxel_position, const float3 bounds) {
    const int3 global_voxel_position = int3_add(chunk_voxel_position, byte3_to_int3(local_position));
    float3 position = int3_to_float3(global_voxel_position);
    float3_multiply_float_p(&position, terrain_voxel_scale);
    position.y += bounds.y / 2.0f; // 0.26f; // 0.75f;
    position.y += 0.05f; // extra
    return position;
}

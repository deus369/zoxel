int real_position_to_voxel_position_dim(const float real_position) {
    float multiplier = default_chunk_length / real_chunk_scale;
    return (int) floor(real_position * multiplier);
}

int3 real_position_to_voxel_position2(const float3 real_position, const float voxel_scale) {
    const float multiplier = 1.0f / voxel_scale; // default_chunk_length / real_chunk_scale;
    return (int3) { (int) floor(real_position.x * multiplier), (int) floor(real_position.y * multiplier), (int) floor(real_position.z * multiplier) };
}

int3 real_position_to_voxel_position(float3 real_position) {
    const float multiplier = default_chunk_length / real_chunk_scale;
    return (int3) { (int) floor(real_position.x * multiplier), (int) floor(real_position.y * multiplier), (int) floor(real_position.z * multiplier) };
}

int3 voxel_position_to_chunk_position(const int3 voxel_position, const int3 chunk_size) {
    int3 voxel_position2 = voxel_position;
    if (voxel_position.x < 0) voxel_position2.x += 1;
    if (voxel_position.y < 0) voxel_position2.y += 1;
    if (voxel_position.z < 0) voxel_position2.z += 1;
    int3 chunk_position = int3_div(voxel_position2, chunk_size);
    // (int3) { voxel_position.x / chunk_size.x, voxel_position.y / chunk_size.y, voxel_position.z / chunk_size.z };
    // because for example -10 / 16 is 0 as an integer, but  coordinates we need a negative chunk position
    if (voxel_position.x < 0) chunk_position.x -= 1;
    if (voxel_position.y < 0) chunk_position.y -= 1;
    if (voxel_position.z < 0) chunk_position.z -= 1;
    return chunk_position;
    // return (int3) { voxel_position.x / chunk_size.x, voxel_position.y / chunk_size.y, voxel_position.z / chunk_size.z };
}

void chunk_position_fix2(const float3 real_position, int3 *chunk_position) {
    if (real_position.x < 0) chunk_position->x -= 1;
    if (real_position.y < 0) chunk_position->y -= 1;
    if (real_position.z < 0) chunk_position->z -= 1;
}

int3 real_position_to_chunk_position(float3 real_position, const int3 chunk_size) {
    int3 voxel_position = real_position_to_voxel_position(real_position);
    if (real_position.x < 0) voxel_position.x += 1;
    if (real_position.y < 0) voxel_position.y += 1;
    if (real_position.z < 0) voxel_position.z += 1;
    int3 chunk_position = (int3) { voxel_position.x / chunk_size.x, voxel_position.y / chunk_size.y, voxel_position.z / chunk_size.z };
    chunk_position_fix2(real_position, &chunk_position);
    return chunk_position;
}

int3 get_local_position(int3 voxel_position, int3 chunk_position, int3 chunk_size) {
    voxel_position.x %= chunk_size.x;
    voxel_position.y %= chunk_size.y;
    voxel_position.z %= chunk_size.z;
    if (voxel_position.x < 0) voxel_position.x = chunk_size.x - 1 + voxel_position.x;
    if (voxel_position.y < 0) voxel_position.y = chunk_size.y - 1 + voxel_position.y;
    if (voxel_position.z < 0) voxel_position.z = chunk_size.z - 1 + voxel_position.z;
    return voxel_position;
}

byte3 get_local_position_byte3(int3 voxel_position, int3 chunk_position, byte3 chunk_size) {
    byte3 local_position;
    if (voxel_position.x < 0) local_position.x = chunk_size.x - 1 + ((voxel_position.x + 1) % chunk_size.x);
    else local_position.x = voxel_position.x % chunk_size.x;
    if (voxel_position.y < 0) local_position.y = chunk_size.y - 1 + ((voxel_position.y + 1) % chunk_size.y);
    else local_position.y = voxel_position.y % chunk_size.y;
    if (voxel_position.z < 0) local_position.z = chunk_size.z - 1 + ((voxel_position.z + 1) % chunk_size.z);
    else local_position.z = voxel_position.z % chunk_size.z;
    return local_position;
}

int3 voxel_chunk_position_xz(int3 chunk_position, int3 chunk_size) {
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    return voxel_position;
}

int3 get_chunk_voxel_position(int3 chunk_position, int3 chunk_size) {
    int3 voxel_position = int3_multiply_int3(chunk_position, chunk_size);
    return voxel_position;
}

float3 voxel_to_real_position(const byte3 local_position, const int3 chunk_position, const byte3 chunk_size, const float voxel_scale) {
    const int3 chunk_position_voxel = int3_multiply_int3(chunk_position, byte3_to_int3(chunk_size));
    const int3 global_voxel_position = int3_add(chunk_position_voxel, byte3_to_int3(local_position));
    float3 position = int3_to_float3(global_voxel_position);
    float3_multiply_float_p(&position, voxel_scale);
    // middle of voxel position
    position.x += voxel_scale / 2;
    position.y += voxel_scale / 2;
    position.z += voxel_scale / 2;
    return position;
}

byte3 find_position_in_chunk(const ChunkOctree *chunk_octree, const byte target_depth) {
    if (chunk_octree == NULL) return byte3_full;
    const byte chunk_length = powers_of_two_byte[target_depth];
    const byte max_checks = 32;
    byte checks_count = 0;
    while (checks_count < max_checks) {
        // get a random x-z position
        byte3 local_position = (byte3) { rand() % chunk_length, chunk_length - 1, rand() % chunk_length };
        // zox_log("   > checking position: %ix%i\n", local_position.x, local_position.z)
        byte3 temp2 = local_position;
        const byte voxel1 = get_octree_voxel(chunk_octree, &temp2, target_depth);
        if (!voxel1) {
            // find ground now
            for (local_position.y = chunk_length - 2; local_position.y >= 0; local_position.y--) {
                byte3 temp = local_position;
                const byte voxel = get_octree_voxel(chunk_octree, &temp, target_depth);
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


byte3 find_position_in_chunk_with_above(const ChunkOctree *chunk_octree, const byte target_depth, const ChunkOctree *chunk_octree_above) {
    if (chunk_octree == NULL) return byte3_full;
    const byte chunk_length = powers_of_two_byte[target_depth];
    const byte max_checks = 32;
    byte checks_count = 0;
    while (checks_count < max_checks && chunk_octree_above) {
        // get a random x-z position
        byte3 local_position = (byte3) { rand() % chunk_length, 0, rand() % chunk_length };
        // zox_log("   > checking position: %ix%i\n", local_position.x, local_position.z)
        byte3 temp2 = local_position;
        const byte voxel1 = get_octree_voxel(chunk_octree_above, &temp2, target_depth);
        if (!voxel1) {
            // find ground now
            for (local_position.y = chunk_length - 1; local_position.y >= 0; local_position.y--) {
                byte3 temp = local_position;
                const byte voxel = get_octree_voxel(chunk_octree, &temp, target_depth);
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

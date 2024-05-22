int real_position_to_voxel_position_dim(const float real_position) {
    float multiplier = default_chunk_length / real_chunk_scale;
    return (int) floor(real_position * multiplier);
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

void chunk_position_fix2(float3 real_position, int3 *chunk_position) {
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

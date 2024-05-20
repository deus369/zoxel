void chunk_position_fix2(float3 real_position, int3 *chunk_position) {
    if (real_position.x < 0) chunk_position->x -= 1;
    if (real_position.y < 0) chunk_position->y -= 1;
    if (real_position.z < 0) chunk_position->z -= 1;
}

int3 get_voxel_position(float3 real_position) {
    float multiplier = default_chunk_length / real_chunk_scale;
    int3 voxel_position = (int3) { (int) floor(real_position.x * multiplier), (int) floor(real_position.y * multiplier), (int) floor(real_position.z * multiplier) };
    return voxel_position;
}

int3 get_chunk_position(float3 real_position, int3 chunk_size) {
    int3 voxel_position = get_voxel_position(real_position);
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

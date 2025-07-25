const byte max_position_checks = 255;

int real_position_to_voxel_position_dim(const float real_position, const byte depth) {
    const byte length = powers_of_two[depth];
    float multiplier = length / real_chunk_scale;
    return (int) floor(real_position * multiplier);
}

int3 real_position_to_voxel_position2(const float3 real_position, const float voxel_scale) {
    const float multiplier = 1.0f / voxel_scale;
    return (int3) { (int) floor(real_position.x * multiplier), (int) floor(real_position.y * multiplier), (int) floor(real_position.z * multiplier) };
}

int3 real_position_to_voxel_position(float3 real_position, const byte depth) {
    const byte length = powers_of_two[depth];
    const float multiplier = length / real_chunk_scale;
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

int3 real_position_to_chunk_position(float3 real_position, const int3 chunk_size, const byte depth) {
    int3 voxel_position = real_position_to_voxel_position(real_position, depth);
    if (real_position.x < 0) voxel_position.x += 1;
    if (real_position.y < 0) voxel_position.y += 1;
    if (real_position.z < 0) voxel_position.z += 1;
    int3 chunk_position = (int3) { voxel_position.x / chunk_size.x, voxel_position.y / chunk_size.y, voxel_position.z / chunk_size.z };
    chunk_position_fix2(real_position, &chunk_position);
    return chunk_position;
}

int3 get_local_position(
    int3 voxel_position,
    int3 chunk_position,
    int3 chunk_size)
{
    voxel_position.x %= chunk_size.x;
    voxel_position.y %= chunk_size.y;
    voxel_position.z %= chunk_size.z;
    if (voxel_position.x < 0) voxel_position.x = chunk_size.x - 1 + voxel_position.x;
    if (voxel_position.y < 0) voxel_position.y = chunk_size.y - 1 + voxel_position.y;
    if (voxel_position.z < 0) voxel_position.z = chunk_size.z - 1 + voxel_position.z;
    return voxel_position;
}

static inline byte3 get_local_position_byte3(
    int3 voxel_position,
    int3 chunk_position,
    byte3 chunk_size)
{
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

float3 voxel_to_real_position(
    const byte3 local_position,
    const int3 chunk_position,
    const byte3 chunk_size,
    const float voxel_scale)
{
    const int3 chunk_position_voxel = int3_multiply_int3(chunk_position, byte3_to_int3(chunk_size));
    const int3 global_voxel_position = int3_add(chunk_position_voxel, byte3_to_int3(local_position));
    float3 position = int3_to_float3(global_voxel_position);
    float3_scale_p(&position, voxel_scale);
    // middle of voxel position
    position.x += voxel_scale / 2;
    position.y += voxel_scale / 2;
    position.z += voxel_scale / 2;
    return position;
}

float3 voxel_position_to_real_position(
    const int3 voxel_position,
    const byte3 chunk_size,
    const float voxel_scale)
{
    float3 position = int3_to_float3(voxel_position);
    float3_scale_p(&position, voxel_scale);
    // middle of voxel position
    position.x += voxel_scale / 2;
    position.y += voxel_scale / 2;
    position.z += voxel_scale / 2;
    return position;
}

float3 local_to_real_position_character(
    const byte3 in_chunk_position,
    const int3 chunk_grid_position,
    const float3 bounds,
    const byte depth,
    const float vox_scale)
{
    const float scale = get_terrain_voxel_scale(depth) * vox_scale;
    const int3 grid_position = int3_add(chunk_grid_position, byte3_to_int3(in_chunk_position));
    float3 position = int3_to_float3(grid_position);
    // zox_log("scale: %f", scale)
    float3_scale_p(&position, scale);
    position.x += scale / 2.0f;
    position.z += scale / 2.0f;
    position.y += bounds.y / 2.0f;
    position.y += 0.05f; // extra
    return position;
}
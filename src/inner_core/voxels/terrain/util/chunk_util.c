// pass in camera datas
bounds calculate_chunk_bounds(const float3 position3D, const int3 chunk_size, const float vox_scale) {
    const float3 extents = float3_multiply_float(float3_from_int3(chunk_size), vox_scale * 0.5f);
    const float3 bounds_position = float3_add(position3D, extents);
    // zox_log(" cb2 c[%.0fx%.0fx%.0f] e[%.0fx%.0fx%.0f]\n", bounds_position.x, bounds_position.x, bounds_position.y, extents.y, extents.z, extents.z)
    return (bounds) { bounds_position, extents };
}

// returns simple camera distance for chunks
unsigned char get_camera_chunk_distance(const int3 camera_position, const int3 chunk_position) {
    return int_max(int_abs(chunk_position.x - camera_position.x), int_abs(chunk_position.z - camera_position.z));
}

unsigned char get_voxes_lod_from_camera_distance(const unsigned char distance_to_camera) {
    unsigned char lod;
    if (distance_to_camera <= init_lod_voxes) lod = 0;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 1) lod = 1;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 2) lod = 2;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 3) lod = 3;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 4) lod = 4;
    else lod = 255;
    if (lod < min_character_vox_lod) lod = min_character_vox_lod;
    return lod;
}

unsigned char get_block_voxes_lod_from_camera_distance(const unsigned char distance_to_camera) {
    unsigned char lod;
    if (distance_to_camera <= init_lod_voxes) lod = 0;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 1) lod = 1;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 2) lod = 2;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 3) lod = 3;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 4) lod = 4;
    else lod = 255;
    if (lod < min_block_vox_lod) lod = min_block_vox_lod;
    return lod;
}

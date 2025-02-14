byte get_terrain_lod_from_camera_distance(byte distance_to_camera, byte max_camera_distance) {
    #ifdef zox_disable_terrain_lod_levels
    return 0;
    #endif
    if (distance_to_camera >= max_camera_distance) return render_lod_invisible;
    if (distance_to_camera <= initial_terrain_lod) return max_octree_depth - 5;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor) return max_octree_depth - 4;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 2) return max_octree_depth - 3;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 3) return max_octree_depth - 2;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 4) return max_octree_depth - 1;
    else if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * 5) return max_octree_depth;
    else return render_lod_invisible;
}

bounds calculate_chunk_bounds(const float3 position3D, const int3 chunk_size, const float vox_scale) {
    const float3 extents = float3_multiply_float(float3_from_int3(chunk_size), vox_scale * 0.5f);
    const float3 bounds_position = float3_add(position3D, extents);
    // zox_log(" cb2 c[%.0fx%.0fx%.0f] e[%.0fx%.0fx%.0f]\n", bounds_position.x, bounds_position.x, bounds_position.y, extents.y, extents.z, extents.z)
    return (bounds) { bounds_position, extents };
}

// returns simple camera distance for chunks
byte get_camera_chunk_distance(const int3 camera_position, const int3 chunk_position) {
    return (byte) int3_max(chunk_position, camera_position);
}

byte get_voxes_lod_from_camera_distance(const byte distance_to_camera) {
    byte lod;
    if (distance_to_camera <= init_lod_voxes) lod = 0;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 1) lod = 1;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 2) lod = 2;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 3) lod = 3;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 4) lod = 4;
    else lod = render_lod_invisible;
    if (lod < min_character_vox_lod) lod = min_character_vox_lod;
    return lod;
}

byte get_block_voxes_lod_from_camera_distance(const byte distance_to_camera) {
    byte lod;
    if (distance_to_camera <= init_lod_voxes) lod = 0;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 1) lod = 1;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 2) lod = 2;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 3) lod = 3;
    else if (distance_to_camera <= init_lod_voxes + lod_div_voxes * 4) lod = 4;
    else lod = 255;
    if (lod < min_block_vox_lod) lod = min_block_vox_lod;
    return lod;
}

byte get_terrain_lod_from_camera_distance(byte distance_to_camera, byte max_camera_distance, const byte max_depth) {
#ifdef zox_disable_terrain_lod_levels
    return 0;
#endif
    if (distance_to_camera >= max_camera_distance) {
        return render_lod_invisible;
    }
    for (int i = 0; i <= max_depth; i++) {
        if (distance_to_camera <= initial_terrain_lod + terrain_lod_dividor * i) {
            return i;
        }
    }
    return render_lod_invisible;
}

// returns simple camera distance for chunks
byte get_camera_chunk_distance(const int3 camera_position, const int3 chunk_position) {
    return (byte) int3_max(chunk_position, camera_position);
}

byte get_camera_chunk_distance_xz(const int3 camera_position, const int3 chunk_position) {
    return (byte) int3_max_xz((int3) { chunk_position.x, 0, chunk_position.z }, camera_position);
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
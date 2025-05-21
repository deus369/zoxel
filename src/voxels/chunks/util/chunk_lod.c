byte get_chunk_terrain_depth_from_lod(const byte lod, const byte max_depth) {
    return max_depth - lod;
}

byte get_chunk_division_from_lod(const byte lod, const byte max_depth) {
    return max_depth - lod;
}
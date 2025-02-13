byte get_chunk_division_from_lod_colors(const byte lod) {
    return max_octree_depth - lod;
}

byte get_chunk_terrain_depth_from_lod(const byte lod) {
    return max_octree_depth - lod;
}

byte get_chunk_division_from_lod(const byte lod) {
    return max_octree_depth - lod;
}

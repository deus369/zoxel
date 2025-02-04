unsigned char get_chunk_division_from_lod_colors(const unsigned char lod) {
    return max_octree_depth - lod;
}

unsigned char get_chunk_terrain_depth_from_lod(const unsigned char lod) {
    return max_octree_depth - lod;
}

unsigned char get_chunk_division_from_lod(const unsigned char lod) {
    return max_octree_depth - lod;
}

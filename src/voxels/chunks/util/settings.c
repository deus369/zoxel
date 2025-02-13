void set_terrain_voxel_scale(byte depth) {
    terrain_voxel_scale = real_chunk_scale / ((float) powers_of_two[depth]);
}

void set_max_octree_length(byte new_max_octree_depth) {
    max_octree_depth = new_max_octree_depth;
    default_chunk_length = powers_of_two[max_octree_depth];
    default_chunk_size = (int3) { default_chunk_length, default_chunk_length, default_chunk_length };
    default_chunk_size_byte3 = int3_to_byte3(default_chunk_size);
    // byte default_chunk_length_b = powers_of_two_byte[max_octree_depth];
    // default_chunk_size_byte3 = (byte3) { default_chunk_length_b, default_chunk_length_b, default_chunk_length_b };
    set_terrain_voxel_scale(max_octree_depth);
    // zox_log(" > set max octree depth [%i] - chunk length [%i] - voxel scale [%f]\n", max_octree_depth, default_chunk_length, terrain_voxel_scale);
}

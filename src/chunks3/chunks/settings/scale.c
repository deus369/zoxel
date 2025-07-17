const float default_vox_scale = 0.5f;
float vox_model_scale = (1 / 64.0f);
float real_chunk_scale = 16.0f;

// this should be based on the voxscale that it's getting for..
float get_terrain_voxel_scale(const byte depth) {
    return real_chunk_scale / ((float) powers_of_two[depth]);
}

float get_terrain_voxel_scale_inverse(const byte depth) {
    return 1.0f /  get_terrain_voxel_scale(depth);
}
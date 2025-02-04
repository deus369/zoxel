// #define zox_debug_chunks // use to debug chunk edges

// 0 for max, 255 hidden?
const unsigned char min_block_vox_lod = 0;
const unsigned char min_character_vox_lod = 0;

const float default_vox_scale = 0.5f;
const double max_chunk_process_time = 0; // 0.001;
const unsigned char is_select_minis = 0;
const float overall_voxel_scale = 32.0f; // 64.0f; // 4.0f // 2.0f;
const float3 center_mesh_offset = { 0, 0, 0 };
const int dissapearChance = 92;
unsigned char max_octree_depth = 5; // 4
int default_chunk_length; // = powers_of_two[max_octree_depth];
int3 default_chunk_size;
byte3 default_chunk_size_byte3;
const float real_chunk_scale = 16.0f; // overall_voxel_scale / ((float) octree_node_size);
float terrain_voxel_scale = 1.0f;
const int fill_octree_random_rate = 50;
const int fill_octree_random_rate2 = 40;
const int fill_octree_random_rate3 = 30;

const float octree_scales3[] = {
    2.0f * real_chunk_scale,
    1.0f * real_chunk_scale,
    0.5f * real_chunk_scale,
    0.25f * real_chunk_scale,
    0.125f * real_chunk_scale,
    0.0625f * real_chunk_scale,
    0.03125f * real_chunk_scale,
    0.015625f * real_chunk_scale,
    0.0078125f * real_chunk_scale
};

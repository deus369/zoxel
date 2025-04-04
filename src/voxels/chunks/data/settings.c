// debug options
// #define zox_debug_chunks // use to debug chunk edges
// #define zox_debug_chunk_link_system
// #define zox_debug_chunk_link_system_test
// #define zox_debug_hit_point
// #define zox_debug_hit_normal
// 0 for max, 255 hidden?
const byte min_block_vox_lod = 0;
const byte min_character_vox_lod = 0;
const float default_vox_scale = 0.5f;
const double max_chunk_process_time = 0; // 0.001;
const byte is_select_minis = 0;
const float overall_voxel_scale = 32.0f; // 64.0f; // 4.0f // 2.0f;
const float3 center_mesh_offset = { 0, 0, 0 };
const int dissapearChance = 92;
const float real_chunk_scale = 16.0f; // overall_voxel_scale / ((float) octree_node_size);
byte max_octree_depth = 5; // 4
int default_chunk_length; // = powers_of_two[max_octree_depth];
int3 default_chunk_size;
byte3 default_chunk_size_byte3;
float terrain_voxel_scale = 1.0f;
const int fill_octree_random_rate = 50;
const int fill_octree_random_rate2 = 40;
const int fill_octree_random_rate3 = 30;
const int init_lod_voxes = 1;
const int lod_div_voxes = 1;
const byte terrain_lod_dividor = 2; // 2 | 3
byte initial_terrain_lod = 1; // 3 | 2
const uint safety_checks_raycasting = 512;
// const float ray_interval = 0.04f;
const float terrain_ray_length = 8;
const float raycast_thickness = 10;
const color_rgb raycast_quad_color  = (color_rgb) { 194, 194, 194 };
byte is_render_chunk_edges = 0;
#include "color.c"
#include "raycast.c"
#include "scale.c"

// debug options
// #define zox_debug_chunks // use to debug chunk edges
// #define zox_debug_chunk_link_system
// #define zox_debug_chunk_link_system_test
// #define zox_debug_hit_point
// #define zox_debug_hit_normal
// 0 for max, 255 hidden?
const byte min_block_vox_lod = 0;
const byte min_character_vox_lod = 0;
const double max_chunk_process_time = 0; // 0.001;
const byte is_select_minis = 0;
const float3 center_mesh_offset = { 0, 0, 0 };
const int dissapearChance = 92;
// int default_chunk_length;
const int fill_octree_random_rate = 50;
const int fill_octree_random_rate2 = 40;
const int fill_octree_random_rate3 = 30;
const uint safety_checks_raycasting = 512;
const float raycast_thickness = 10;
const color_rgb raycast_quad_color  = (color_rgb) { 194, 194, 194 };
byte is_render_chunk_edges = 0;

// Camera
byte init_lod_voxes = 1;
byte lod_div_voxes = 2;
byte initial_terrain_lod = 2; // 3 | 2
byte terrain_lod_dividor = 3; // 2 | 3
#include "color.c"
#include "raycast.c"
#include "scale.c"
#include "lod.c"
// debug options
// #define zox_debug_chunks // use to debug chunk edges
// #define zox_debug_chunk_link_system
// #define zox_debug_chunk_link_system_test
// #define zox_debug_hit_point
// #define zox_debug_hit_normal
// 0 for max, 255 hidden?
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
byte is_render_chunk_edges = 0;
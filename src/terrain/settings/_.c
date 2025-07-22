const float end_game_delay = 0.8f;
const float end_game_delay2 = 1.0f;
const double start_game_delay_terrain = 1.5;
const double start_game_delay_terrain2 = 2.5;
const float end_game_delay_fade = 1;
// others
byte block_vox_render_at_lod = 0; // 3 | 4 looks best
byte zox_log_terrain_generation = 0;
// voxes lods
const byte max_vox_blocks = 16; // max spawned vox_blocks
const byte max_lod_voxes = 0;

// const int max_chunks_build_per_frame = 32; // 16; // terrain chunks built per frame
byte high_resolution_terain_lod = 1; // 2 | 1
byte terrain_spawn_distance;
byte terrain_vertical = 2;
byte terrain_size = 0;

// uint terrain_seed = 32666;
#define terrain_texture_resolution 16 // 32
#define octree_min_height -1.995f // 0.005f
#define noise_positiver2 32000
#define terrain_minus_amplifier 0.0
const int2 chunk_texture_size = { terrain_texture_resolution, terrain_texture_resolution };

#define zox_biome_grassland 0
#define zox_biome_desert 1
#define zox_biome_savanna 2
#define zox_biome_forest 3
#define zox_biome_swamp 4
#define zox_biome_mountain 5
#define zox_biome_end 6

#include "grassy_plains.c"
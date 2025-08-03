byte terrain_obsidian_height = 3;   // 1 | 2 | 3 | 4

const int sand_height = -10;
const int mountain_height = 20;
const byte terrain_min_height = 8;
const int terrain_octaves = 12;
const float flat_height_level = -0.56f; // 0.2f;
// double terrain_amplifier = 64.0;
double terrain_boost = 0.0;
int lowest_voxel_height = -24;
double terrain_frequency = 0.007216;

// blocks
uint block_spawn_chance_grass = 512;
// #define block_spawn_chance_grass 512 // 128 | 256 | 512 | 1024 | 2048 | 4096
#define block_spawn_chance_flower 32 // 16 32 64 128 flowers
#define block_spawn_chance_rubble 47
#define octree_random_spawn_chance 22
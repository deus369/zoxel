byte block_vox_render_at_lod = 0; // 3 | 4 looks best

byte zox_log_terrain_generation = 0;
// voxes lods
const byte max_vox_blocks = 16; // max spawned vox_blocks
const byte max_lod_voxes = 0;
// terrain
const int sand_height = -10;
const int mountain_height = 20;
// blocks
uint block_spawn_chance_grass = 512;
// #define block_spawn_chance_grass 512 // 128 | 256 | 512 | 1024 | 2048 | 4096
#define block_spawn_chance_flower 32 // 16 32 64 128 flowers
#define block_spawn_chance_rubble 47
#define octree_random_spawn_chance 22

// const int max_chunks_build_per_frame = 32; // 16; // terrain chunks built per frame
byte high_resolution_terain_lod = 1; // 2 | 1
byte terrain_spawn_distance;
byte terrain_vertical = 2;
const byte terrain_min_height = 8;
const int terrain_octaves = 12;
const float flat_height_level = -0.56f; // 0.2f;
byte terrain_size = 0;
double terrain_amplifier = 64.0;
double terrain_boost = 0.0;
int lowest_voxel_height = -24;
const double real_terrain_frequency = 0.007216; //  0.013216; //  0.008216; // 0.004216; // 0.026216
double terrain_frequency = 0; // 0.038216;
// uint32_t terrain_seed = 32666;
#define terrain_mode_tiny 1
#define terrain_mode_medium 2
#define terrain_mode_large 3
#define terrain_texture_resolution 16 // 32
#define octree_min_height -1.995f // 0.005f
#define noise_positiver2 32000
#define terrain_minus_amplifier 0.0
const int2 chunk_texture_size = { terrain_texture_resolution, terrain_texture_resolution };

void print_terrain_settings() {
    zox_log(" > terrain settings set\n")
    // zox_log("     + terrain seed is [%i]\n", (int) terrain_seed)
    zox_log("     + terrain_depth is [%i]\n", terrain_depth)
    zox_log("     + render distance is [%i]\n", terrain_spawn_distance)
    zox_log("     + terrain vertical is [%i]\n", terrain_vertical)
    zox_log("     + lod dividor is [%i]\n", terrain_lod_dividor)
    zox_log("     + height amplifier is [%d]\n", terrain_amplifier)
    zox_log("     + height noise frequency is [%d]\n", terrain_frequency)
    zox_log("     + height boost is [%d]\n", terrain_boost)
    zox_log("     + lowest low is [%d]\n", lowest_voxel_height)
}

void process_arguments_terrain(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--tiny") == 0) {
            terrain_size = terrain_mode_tiny;
            zox_log(" + tiny mode enabled\n")
        } else if (strcmp(args[i], "--medium") == 0) {
            terrain_size = terrain_mode_medium;
        } else if (strcmp(args[i], "--large") == 0) {
            terrain_size = terrain_mode_large;
        }
    }
}
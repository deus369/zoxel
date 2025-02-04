// const int max_chunks_build_per_frame = 32; // 16; // terrain chunks built per frame
unsigned char high_resolution_terain_lod = 1; // 2 | 1
unsigned char terrain_spawn_distance;
unsigned char terrain_vertical = 2;
const unsigned char terrain_min_height = 8;
const int terrain_octaves = 12;
const float flat_height_level = -0.56f; // 0.2f;
unsigned char terrain_mode = 0;
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
    zox_log("     + octree depth is [%i]\n", max_octree_depth)
    zox_log("     + render distance is [%i]\n", terrain_spawn_distance)
    zox_log("     + terrain vertical is [%i]\n", terrain_vertical)
    zox_log("     + lod dividor is [%i]\n", terrain_lod_dividor)
    zox_log("     + height amplifier is [%d]\n", terrain_amplifier)
    zox_log("     + height noise frequency is [%d]\n", terrain_frequency)
    zox_log("     + height boost is [%d]\n", terrain_boost)
    zox_log("     + lowest low is [%d]\n", lowest_voxel_height)
}

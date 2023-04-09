int terrain_spawn_distance;
int terrain_vertical = 2;
const unsigned char terrain_min_height = 8;
double terrain_amplifier = 64.0;
double terrain_boost = 0.0;
int lowest_voxel_height = -24;
int inner_render_buffer = 1;
int lod_division_dividor = 3;
const int max_chunks_build_per_frame = 32;
// float real_chunk_scale = overall_voxel_scale / 2.0f; // 1.0f;   // size achunk takes up
#define terrain_texture_resolution 32 // 16
const int2 chunk_texture_size = { terrain_texture_resolution, terrain_texture_resolution };
#ifndef WEB_BUILD
#else
    #define voxels_disable_streaming
#endif
#define octree_min_height -1.995f // 0.005f
#define noise_positiver2 32000
// #define terrain_amplifier 64.0
#define terrain_minus_amplifier 0.0
#ifdef voxel_octrees
    double terrain_frequency = 0.028216; // 0.026216
#else
    double terrain_frequency = 0.00216; // 0.004216
#endif
// const int3 terrain_chunk_size = { chunk_length, 8 * chunk_length, chunk_length };
const int terrain_octaves = 12;
const uint32_t terrain_seed = 32666;
const float flat_height_level = -0.56f; // 0.2f;

void set_terrain_render_distance() {
    if (cpu_tier == 3) {
        terrain_spawn_distance = 16; // 26;
        terrain_vertical = 3; // 4;
        lod_division_dividor = 4; // 5;
        // set_max_octree_length(5);
    } else if (cpu_tier == 2) {
        terrain_spawn_distance = 12;
        lod_division_dividor = 3;
    } else if (cpu_tier == 1) {
        terrain_spawn_distance = 8;
    } else {
        terrain_spawn_distance = 4;
    }
    terrain_frequency = max_octree_depth * 2 * 0.008216;
    terrain_boost = -12 * terrain_vertical + max_octree_depth * 4;
    terrain_amplifier = terrain_vertical * 16;
    lowest_voxel_height = - terrain_vertical * 16 + 1;
    zoxel_log(" > terrain settings set\n");
    zoxel_log("     + octree depth is [%i]\n", max_octree_depth);
    zoxel_log("     + render distance is [%i]\n", terrain_spawn_distance);
    zoxel_log("     + terrain vertical is [%i]\n", terrain_vertical);
    zoxel_log("     + lod dividor is [%i]\n", lod_division_dividor);
    zoxel_log("     + height amplifier is [%d]\n", terrain_amplifier);
    zoxel_log("     + height noise frequency is [%d]\n", terrain_frequency);
    zoxel_log("     + height boost is [%d]\n", terrain_boost);
    zoxel_log("     + lowest low is [%d]\n", lowest_voxel_height);
}

// inner_render_buffer = 1;
// terrain_frequency = 0.016216;
// terrain_frequency = 0.136216;
// #define zox_pip_voxels EcsOnUpdate | EcsPreStore | EcsOnLoad
#define zox_pip_voxels_chunk_dirty EcsOnLoad // sets chunk dirty 1 -  generates voxel data
#define zox_pip_voxels EcsOnUpdate // uses event states
#define zox_pip_voxels_chunk_clean EcsPostUpdate // generates mesh data, resets chunk_dirty
// base on zox_pip_mainthread EcsPreStore
// #define zox_pip_voxels_build EcsPreUpdate // generates meshes | EcsPostUpdate
const float overall_voxel_scale = 32.0f; // 64.0f; // 4.0f // 2.0f;
const float3 center_mesh_offset = { 0, 0, 0 };
const int dissapearChance = 92;
int max_octree_depth = 5; // 4
int default_chunk_length; // = powers_of_two[max_octree_depth];
int3 default_chunk_size; // = (int3) { default_chunk_length, default_chunk_length, default_chunk_length };
byte3 default_chunk_size_byte3;
const float real_chunk_scale = 16.0f; // overall_voxel_scale / ((float) octree_node_size);
float terrain_voxel_scale = 1.0f;

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

void set_terrain_voxel_scale(unsigned char depth) {
    terrain_voxel_scale = real_chunk_scale / ((float) powers_of_two[depth]);
}

void set_max_octree_length(unsigned char new_max_octree_depth) {
    max_octree_depth = new_max_octree_depth;
    default_chunk_length = powers_of_two[max_octree_depth];
    default_chunk_size = (int3) { default_chunk_length, default_chunk_length, default_chunk_length };
    unsigned char default_chunk_length_b = powers_of_two_byte[max_octree_depth];
    default_chunk_size_byte3 = (byte3) { default_chunk_length_b, default_chunk_length_b, default_chunk_length_b };
    set_terrain_voxel_scale(max_octree_depth);
    // zoxel_log(" > set max octree depth [%i] - chunk length [%i] - voxel scale [%f]\n", max_octree_depth, default_chunk_length, terrain_voxel_scale);
}

const float overall_voxel_scale = 32.0f; // 64.0f; // 4.0f // 2.0f;
const float real_chunk_scale = 16.0f; // overall_voxel_scale / ((float) octree_node_size);
const float3 center_mesh_offset = { 0, 0, 0 };
const double noiseChunkAnimateSpeed = 0.5; // 1 / 8.0;
const int dissapearChance = 92;
const float spawnRange = 0.96f;
int max_octree_depth = 4;
int default_chunk_length; // = powers_of_two[max_octree_depth];
int3 default_chunk_size; // = (int3) { default_chunk_length, default_chunk_length, default_chunk_length };

void set_max_octree_length(unsigned char new_max_octree_depth) {
    max_octree_depth = new_max_octree_depth;
    default_chunk_length = powers_of_two[max_octree_depth];
    default_chunk_size = (int3) { default_chunk_length, default_chunk_length, default_chunk_length };
    // zoxel_log(" > set max octree depth [%i] - chunk length [%i] \n", max_octree_depth, default_chunk_length);
}
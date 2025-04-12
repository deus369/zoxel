const float default_vox_scale = 0.5f;
const float real_chunk_scale = 16.0f;
const float overall_voxel_scale = 32.0f;
float terrain_voxel_scale = 1.0f;
byte max_octree_depth = 5; // 4
int3 default_chunk_size;
byte3 default_chunk_size_byte3;
const byte max_octree_depth_character = 5; // issue with this...!
#define vox_model_scale (1 / 64.0f) // * 1.6f
#define player_vox_scale  (1 / 64.0f) // * 1.6f
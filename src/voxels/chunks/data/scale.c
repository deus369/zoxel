const float default_vox_scale = 0.5f;
const float real_chunk_scale = 16.0f;
float terrain_voxel_scale = 0.5f;   // set to 0.5
byte max_octree_depth = 5; // 4 | 5
int3 default_chunk_size;
byte3 default_chunk_size_byte3;
byte max_octree_depth_character = 5; // issue with this...!
#define vox_model_scale (1 / 64.0f) // * 1.6f
#define player_vox_scale  (1 / 64.0f) // * 1.6f
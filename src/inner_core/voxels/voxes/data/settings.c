#define vox_model_scale (1 / 64.0f)
const unsigned char max_octree_depth_character = 5; // issue with this...!
#define monsters_directory "voxes"character_slash
int files_voxes_count = 0;
ecs_entity_t *files_voxes;
string_hashmap *files_hashmap_voxes;

// GenerateVox == 1
const unsigned char is_generate_vox_airs = 1;
const unsigned char is_generate_vox_outlines = 1;
const float fracture_dark_multiplier = 0.6f; // 0.13f
const float grass_blend_dark_multiplier = 0.8f; // 0.13f

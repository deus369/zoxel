#define directory_voxes "voxes"
const byte max_vox_file_lods = 5;
int files_voxes_count = 0;
ecs_entity_t *files_voxes;
string_hashmap *files_hashmap_voxes;

// GenerateVox == 1
byte is_generate_vox_outlines = 1; // 0 | 1
const byte is_generate_vox_airs = 1;
const float fracture_dark_multiplier = 0.6f; // 0.13f
const float grass_blend_dark_multiplier = 0.8f; // 0.13f

void process_arguments_voxes(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--disableoutlines") == 0) {
            is_generate_vox_outlines = 0;
        } else if (strcmp(args[i], "--enableoutlines") == 0) {
            zox_log("+ enabling block outlines")
            is_generate_vox_outlines = 1;
        } else if (strcmp(args[i], "--noblockvoxes") == 0 || strcmp(args[i], "--nominivoxes") == 0) {
            zox_log("+ disabling block voxes")
            disable_block_voxes = 1;
        }
    }
}
// important
#define scale_volumes 1 // debug 0.1 / 1
// max soudn length
#define sound_play_death_delay 4 // keep big incase lag, we dont want to destroy while playing
#define channel_sample_rate 44100
#define sound_sample_rate 44100 // / 8
// #define sound_sample_rate 4410 // 2205
#define sample_rate_f (float) sound_sample_rate
#define static_sounds_length 5
const int channels_count = 2;   // 2
const float sound_attack_multiplier = 0.02f; // 0.04f
const float sound_dampen_multiplier = 0.7f; // 0.92f
const float sound_noise = 0.0f;
byte zox_visualize_sounds = 0;
#define sound_display_skip_rate 36
#define sound_display_start 0.0f
#define sound_display_end 1.0f
const float debug_sound_thickness = 0.01f;  // 0.1f
const float default_sound_volume = 1.0f; // 0.5f
const float sound_generation_splitter = 8;
// volumes
const float default_sound_volume_loaded = 0.3f *scale_volumes;
int global_master_volume = 16 * scale_volumes;
const int global_master_volume_max = 128 * scale_volumes;
const int global_master_volume_increment = 8 * scale_volumes;
// files
#define directory_sounds "sounds"
int sound_files_count = 0;
ecs_entity_t *files_sounds;
string_hashmap *files_hashmap_sounds;
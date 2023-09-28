// #define sound_sample_rate 44100
#define sound_sample_rate 2205
#define sample_rate_f (float) sound_sample_rate
#define static_sounds_length 5
const int channels_count = 1;   // 2
const float sound_attack_multiplier = 0.02f; // 0.04f
const float sound_dampen_multiplier = 0.7f; // 0.92f
const float sound_noise = 0.02f; // 0.04
unsigned char zox_visualize_sounds = 0;
#define sound_display_skip_rate 36
#define sound_display_start 0.0f
#define sound_display_end 1.0f
const float debug_sound_thickness = 0.01f;  // 0.1f
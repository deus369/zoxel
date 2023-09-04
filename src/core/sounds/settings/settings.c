#define sound_sample_rate 44100 // / 2
#define sample_rate_f 44100.0f // / 2.0f
#define static_sounds_length 5
#ifdef zoxel_debug_sounds
    #define sound_display_skip_rate 35
    #define sound_display_start 0.0f
    #define sound_display_end 1.0f
#endif
const int channels_count = 1;   // 2
const float sound_attack_multiplier = 0.02f; // 0.04f
const float sound_dampen_multiplier = 0.7f; // 0.92f
const float sound_noise = 0.02f; // 0.04
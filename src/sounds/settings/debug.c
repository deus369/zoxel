byte audio_enabled = 0;
byte is_log_sounds = 0;
#define zox_log_sounds(msg, ...)\
    if (is_log_sounds) {\
        zox_log(msg, ##__VA_ARGS__)\
    }

byte zox_visualize_sounds = 0;
#define sound_display_skip_rate 36
#define sound_display_start 0.0f
#define sound_display_end 1.0f
const float debug_sound_thickness = 0.01f;  // 0.1f
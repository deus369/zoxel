byte is_log_notes = 0;
#define zox_log_notes(msg, ...)\
    if (is_log_notes) {\
        zox_log(msg, ##__VA_ARGS__)\
    }

// instrument_piano_file | instrument_piano
const byte music_load_instrument = instrument_piano_file;
float global_music_speed = 1;
const int music_note_skip = 89;
const int music_play_double_chance = 89;
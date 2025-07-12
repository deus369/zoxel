byte is_log_notes = 0;
#define zox_log_notes(msg, ...)\
    if (is_log_notes) {\
        zox_log(msg, ##__VA_ARGS__)\
    }

#define zox_test_music_files
const int music_note_skip = 89;
// instrument_piano_file | instrument_piano
const byte music_load_instrument = instrument_piano_file;
float global_music_speed = 0.5f;
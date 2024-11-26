#ifndef zox_mod_musics_midi_note
#define zox_mod_musics_midi_note
#define MAX_NOTES 128

typedef struct {
    double time;
    double length;
    double frequency;
} MidiNote;

#endif

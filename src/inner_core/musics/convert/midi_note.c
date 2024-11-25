#ifndef zox_mod_musics_midi_note
#define zox_mod_musics_midi_note

#define MAX_NOTES 128

// Structure to store the note event data
typedef struct {
    double frequency;
    double time;
    double length;
} MidiNote;

#endif

#include <stdio.h>
#include <math.h>
#include "midi_note.c"


// Save the notes to a file
int save_notes_to_file(MidiNote *notes, int note_count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for saving");
        return -1;
    }
    fwrite(&note_count, sizeof(int), 1, file); // Write the number of notes
    fwrite(notes, sizeof(MidiNote), note_count, file); // Write the notes data
    /*for (int i = 0; i < note_count; i++) {
        MidiNote note = notes[i];
        fwrite(&note.time, sizeof(double), 1, file);
        fwrite(&note.length, sizeof(double), 1, file);
        fwrite(&note.frequency, sizeof(double), 1, file);
    }*/
    fclose(file);
    return 0;
}

#include <stdio.h>
#include <math.h>
#include "midi_note.c"

// Load the notes from a file
int load_notes_from_file(MidiNote *notes, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for loading");
        return -1;
    }
    int note_count;
    fread(&note_count, sizeof(int), 1, file); // Read the number of notes
    fread(notes, sizeof(MidiNote), note_count, file); // Read the notes data
    fclose(file);
    return note_count;
}

void test_notes_from_file(const char *filename) {
    // Load notes from file (for testing the save/load functionality)
    MidiNote loaded_notes[MAX_NOTES];
    int loaded_note_count = load_notes_from_file(loaded_notes, filename);
    if (loaded_note_count > 0) {
        printf("Notes loaded from %s:\n", filename);
        for (int i = 0; i < loaded_note_count; i++) {
            printf("MidiNote %d - Frequency: %.2f Hz, Start time: %.2f, Length: %.2f\n", i + 1, loaded_notes[i].frequency, loaded_notes[i].time, loaded_notes[i].length);
        }
    } else {
        printf("loaded_note_count is 0.\n");
    }
}

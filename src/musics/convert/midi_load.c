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
    // Read the number of notes
    size_t note_count;
    size_t items_read = fread(&note_count, sizeof(size_t), 1, file);
    // Check for fread errors
    if (items_read < 1) {
        if (ferror(file)) {
            // An error occurred during reading
            perror("(1) Error reading file");
            fclose(file); // Don't forget to close the file
            return 0;
        } else if (feof(file)) {
            // End of file reached, which is not an error
            printf("End of file reached, only %zu items read\n", items_read);
            return 0;
        }
    }
    // Read the notes data
    items_read = fread(notes, sizeof(MidiNote), note_count, file);
    if (items_read < note_count) {
        if (ferror(file)) {
            perror("(2) Error reading file");
            note_count = 0;
        } else if (feof(file)) {
            printf("End of file reached, only %zu items read\n", items_read);
        }
    }
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

// notes = (MidiNote*) malloc(sizeof(MidiNote) * note_count);
/*for (int i = 0; i < note_count; i++) {
 * MidiNote note;
 * fread(&note.time, sizeof(double), 1, file);
 * fread(&note.length, sizeof(double), 1, file);
 * fread(&note.frequency, sizeof(double), 1, file);
 * notes[i] = note;
 } */


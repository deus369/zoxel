#include <stdio.h>
#include <math.h>
#include <smf.h>
#include "midi_note.c"
#include "midi_load.c"

#define FILENAME "resources/music/music.zox"

// Save the notes to a file
int save_notes_to_file(MidiNote *notes, int note_count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for saving");
        return -1;
    }

    fwrite(&note_count, sizeof(int), 1, file); // Write the number of notes
    fwrite(notes, sizeof(MidiNote), note_count, file); // Write the notes data

    fclose(file);
    return 0;
}

// Function to convert MIDI note number to frequency
double midi_note_to_frequency(int note_number) {
    return 440.0 * pow(2.0, (note_number - 69) / 12.0);
}

void debug_midi_file(smf_t *smf) {
    // Iterate over the tracks and events
    for (int i = 0; i < smf->number_of_tracks; i++) {
        smf_track_t *track = smf_get_track_by_number(smf, i + 1);
        // Iterate through events in the track
        smf_event_t *event;
        while ((event = smf_track_get_next_event(track)) != NULL) {
            printf(" > [%i] time [%f] len [%i]\n", event->event_number, event->time_seconds, event->midi_buffer_length);
            if (event->midi_buffer_length >= 3) { // && event->event_number == SMF_EVENT_MIDI) {
                unsigned char status = event->midi_buffer[0] & 0xF0;
                if (status == 0x90 || status == 0x80) {  // Note On or Note Off
                    unsigned char note_number = event->midi_buffer[1];
                    double frequency = midi_note_to_frequency(note_number);
                    printf("        - note %s\n", (status == 0x90) ? "On" : "Off");
                    printf("        - number %i\n", note_number);
                    printf("        - frequency %f\n", frequency);
                } else {
                    printf("    > status [%i]\n", status);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <MIDI file>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    smf_t *smf = smf_load(filename);
    if (!smf) {
        fprintf(stderr, "Error: could not load MIDI file %s\n", filename);
        return 1;
    }

    // debug_midi_file(smf);

    MidiNote notes[MAX_NOTES];
    int note_count = 0;

    // Iterate over the tracks and events
    for (int i = 0; i < smf->number_of_tracks; i++) {
        smf_track_t *track = smf_get_track_by_number(smf, i + 1);
        // Iterate through events in the track
        smf_event_t *event;
        while ((event = smf_track_get_next_event(track)) != NULL) {
            if (event->midi_buffer_length >= 3) {
                unsigned char status = event->midi_buffer[0] & 0xF0;
                unsigned char note_number = event->midi_buffer[1];
                double frequency = midi_note_to_frequency(note_number);
                if (status == 0x90) {  // Note On
                    // Store the start time and frequency when the note is turned on
                    if (note_count < MAX_NOTES) {
                        notes[note_count].frequency = frequency;
                        notes[note_count].time = event->time_seconds;
                        notes[note_count].length = -1;  // Not yet ended
                        note_count++;
                    }
                } else if (status == 0x80) {  // Note Off
                    // Find the corresponding note-on event and mark the length of the note
                    for (int j = 0; j < note_count; j++) {
                        if (notes[j].frequency == frequency && notes[j].length == -1) {
                            notes[j].length = event->time_seconds - notes[j].time;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Save notes to file
    if (save_notes_to_file(notes, note_count, FILENAME) == 0) {
        printf("Notes [%i] saved successfully to %s\n", note_count, FILENAME);
    }

    test_notes_from_file(FILENAME);

    smf_delete(smf);
    return 0;
}

// gcc -std=c99 src/inner_core/musics/convert/midi.c -o build/midi_converter -lm $(pkg-config --cflags --libs glib-2.0 smf) && ./build/midi_converter raw/midis/songa.mid

// gcc -std=c99 src/inner_core/musics/convert/midi.c -o build/midi_converter \
`pkg-config --cflags --libs glib-2.0` -lm -lsmf

// gcc -std=c99 src/inner_core/musics/convert/midi.c -o build/midi_converter -lm  -lsmf
// -smf fails, pkg-config fixes this
// sudo pacman -S libsmf glib2
// sudo apt-get install libsmf-dev
// ./build/midi_converter raw/midis/song_1.mid

/*if (smf_event_is_note_on(event)) {
 * int note_number = smf_event_get_note_number(event);
 * double time_in_seconds = smf_event_get_time_seconds(event);
 * double frequency = midi_note_to_frequency(note_number);
 * printf("Note: %d, Time: %.3f seconds, Frequency: %.2f Hz\n", note_number, time_in_seconds, frequency);
 } */

/*printf("        - time %d: note %s, number: %i, frequency: %f\n",
 e vent->time_seconds, (stat*us == 0x90) ? "On" : "Off",
 note_number, frequency);*/


/*while (event) {
 * if (smf_event_is_note_on(event)) {
 *     int note_number = smf_event_get_note_number(event);
 *     double time_in_seconds = smf_event_get_time_seconds(event);
 *     double frequency = midi_note_to_frequency(note_number);
 *     printf("Note: %d, Time: %.3f seconds, Frequency: %.2f Hz\n", note_number, time_in_seconds, frequency);
 * }
 * event = smf_event_next(event);
 } */


 /*for (event = track->head; event; event = event->next) {
  * if (smf_event_is_note_on(event)) {
  *     int note_number = event->midi_buffer[1];
  *     double time_in_seconds = event->time_seconds;
  *     double frequency = midi_note_to_frequency(note_number);
  *     printf("Note: %d, Time: %.3f seconds, Frequency: %.2f Hz\n", note_number, time_in_seconds, frequency);
  * }
  } */


 // Check event type and handle accordingly
 /*switch (event->event_number) {
  * case SMF_EVENT_MIDI:
  *     printf("MIDI event\n");
  *     break;
  * case SMF_EVENT_META:
  *     printf("Meta event\n");
  *     break;
  * case SMF_EVENT_SYSEX:
  *     printf("SysEx event\n");
  *     break;
  * default:
  *     printf("Unknown event type\n");
  } */

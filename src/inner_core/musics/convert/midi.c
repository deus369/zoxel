// cc -std=c99 src/inner_core/musics/convert/midi.c -o build/midi_converter -lm $(pkg-config --cflags --libs glib-2.0 smf) && ./build/midi_converter raw/midis/song_1.mid
// -smf fails, pkg-config fixes this
// sudo pacman -S libsmf glib2
// sudo apt-get install libsmf-dev
// ./build/midi_converter raw/midis/song_1.mid
#include <stdio.h>
#include <math.h>
#include <smf.h>

// Function to convert MIDI note number to frequency
double midi_note_to_frequency(int note_number) {
    return 440.0 * pow(2.0, (note_number - 69) / 12.0);
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

    // Iterate over the tracks and events
    for (int i = 0; i < smf->number_of_tracks; i++) {
        smf_track_t *track = smf_get_track_by_number(smf, i + 1);
        // Iterate through events in the track
        smf_event_t *event;
        while ((event = smf_track_get_next_event(track)) != NULL) {
            /*if (smf_event_is_note_on(event)) {
                int note_number = smf_event_get_note_number(event);
                double time_in_seconds = smf_event_get_time_seconds(event);
                double frequency = midi_note_to_frequency(note_number);
                printf("Note: %d, Time: %.3f seconds, Frequency: %.2f Hz\n", note_number, time_in_seconds, frequency);
            }*/
            printf(" > [%i] time [%f]\n", event->event_number, event->time_seconds);

            if (event->midi_buffer_length >= 3) { // && event->event_number == SMF_EVENT_MIDI) {
                unsigned char status = event->midi_buffer[0] & 0xF0;
                if (status == 0x90 || status == 0x80) {  // Note On or Note Off
                    unsigned char note_number = event->midi_buffer[1];
                    double frequency = midi_note_to_frequency(note_number);
                    /*printf("        - time %d: note %s, number: %i, frequency: %f\n",
                        event->time_seconds, (status == 0x90) ? "On" : "Off",
                        note_number, frequency);*/
                    printf("        - note %s\n", (status == 0x90) ? "On" : "Off");
                    printf("        - number %i\n", note_number);
                    printf("        - frequency %f\n", frequency);
                }
            }
            // Check event type and handle accordingly
            /*switch (event->event_number) {
                case SMF_EVENT_MIDI:
                    printf("MIDI event\n");
                    break;
                case SMF_EVENT_META:
                    printf("Meta event\n");
                    break;
                case SMF_EVENT_SYSEX:
                    printf("SysEx event\n");
                    break;
                default:
                    printf("Unknown event type\n");
            }*/
        }
        /*while (event) {
            if (smf_event_is_note_on(event)) {
                int note_number = smf_event_get_note_number(event);
                double time_in_seconds = smf_event_get_time_seconds(event);
                double frequency = midi_note_to_frequency(note_number);
                printf("Note: %d, Time: %.3f seconds, Frequency: %.2f Hz\n", note_number, time_in_seconds, frequency);
            }
            event = smf_event_next(event);
        }*/
        /*for (event = track->head; event; event = event->next) {
            if (smf_event_is_note_on(event)) {
                int note_number = event->midi_buffer[1];
                double time_in_seconds = event->time_seconds;
                double frequency = midi_note_to_frequency(note_number);
                printf("Note: %d, Time: %.3f seconds, Frequency: %.2f Hz\n", note_number, time_in_seconds, frequency);
            }
        }*/
    }

    smf_delete(smf);
    return 0;
}

#ifndef zox_mod_musics
#define zox_mod_musics

#define zox_test_music_files
// todo: add note timings, and check them all when playing
//      ^ add two sounds together
// todo: multiple musics, and playlists (musicLinks)
// todo: each music note - will check music start time - get current time, to know when to spawn sound - makes it more dynamic

const int music_note_skip = 89;
const float default_music_volume = 2.2f;
zox_declare_tag(Note)
zox_declare_tag(Music)
zox_declare_tag(Looping)
zox_component_byte(MusicNote)
zox_component_byte(GenerateMusic)
zox_component_byte(MusicPlaying)
zox_component_double(MusicTime)
zox_component_double(MusicSpeed)
zox_entities_component(NoteLinks)
// zox_memory_component(MusicData, int)
#include "util/music_palette.c"
#include "convert/midi_load.c"
#include "prefabs/prefabs.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

void load_music_file(ecs_world_t *world) {
    #define music_file "music"character_slash"music.zox"
    char* music_filepath = concat_file_path(resources_path, music_file);
    zox_log(" > music file: %s\n", music_filepath)
    // test_notes_from_file(music_filepath);
    const ecs_entity_t music = spawn_music(world, prefab_music);
    zox_get_muter(music, NoteLinks, noteLinks)
    MidiNote loaded_notes[MAX_NOTES];
    int loaded_note_count = load_notes_from_file(loaded_notes, music_filepath);
    resize_memory_component(NoteLinks, noteLinks, ecs_entity_t, loaded_note_count)
    zox_log(" > loaded %s :: %i:\n", music_filepath, loaded_note_count)
    if (loaded_note_count > 0) {
        zox_log(" > Notes loaded from %s:\n", music_filepath);
        for (int i = 0; i < loaded_note_count; i++) {
            int note = find_note_index(loaded_notes[i].frequency);
            float test_frequency = note_frequencies[note];
            zox_log("   > MidiNote %d : %i - Frequency: %.2f Hz, Start time: %.2f, Length: %.2f, test_frequency: %f\n", i + 1, note, loaded_notes[i].frequency, loaded_notes[i].time, loaded_notes[i].length, test_frequency);
            noteLinks->value[i] = spawn_note(world, prefab_note, note, instrument_piano, loaded_notes[i].length, 1);
        }
    }
    free(music_filepath);
}

zox_begin_module(Musics)
zox_define_tag(Note)
zox_define_tag(Music)
zox_define_tag(Looping)
zox_define_component_byte(MusicNote)
zox_define_component_byte(GenerateMusic)
zox_define_component_byte(MusicPlaying)
zox_define_component_double(MusicTime)
zox_define_component_double(MusicSpeed)
// zox_define_memory_component(MusicData)
zox_define_entities_component(NoteLinks)
// zox_system_1(MusicGenerateSystem, zox_pip_mainthread, [out] GenerateMusic, [out] NoteLinks, [none] Music)
zox_system_1(MusicPlaySystem, zox_pip_mainthread, [in] MusicPlaying, [in] NoteLinks, [in] MusicSpeed, [in] InstrumentType, [out] MusicNote, [out] MusicTime, [none] Music)
spawn_prefabs_musics(world);
#ifdef zox_test_music_files
load_music_file(world);
#endif
zoxel_end_module(Musics)

#endif

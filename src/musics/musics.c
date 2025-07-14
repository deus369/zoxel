#ifndef zox_mod_musics
#define zox_mod_musics

// todo: make sub modules:
//      - notes
//      - songs
//      - playlists
//      - io

#include "settings/_.c"
byte nomusic = 0;
#define playlist_mode_loop 0    // stick on same track
#define playlist_mode_cycle 1   // play through list sequentially
#define playlist_mode shuffle 2 // random non repeating track each time
zox_declare_tag(Note)
zox_declare_tag(Music)
zox_declare_tag(Looping)
zox_component_byte(MusicNote)
zox_component_byte(GenerateMusic)
zox_component_byte(MusicEnabled)
zox_component_double(MusicLength)
zox_component_double(MusicTime)
zox_component_double(MusicSpeed)
zox_entities_component(NoteLinks)
// playlist
zox_declare_tag(Playlist)
zox_component_byte(PlaylistEnabled)
zox_component_byte(MusicPlaying)
zox_entities_component(MusicLinks)
// realm
zox_component_byte(PlaylistPlaying)
zox_entities_component(PlaylistLinks)
zox_component_entity(PlaylistLink)
// playlist mode
zox_component_byte(PlaylistMode)

// zox_memory_component(MusicData, int)
#include "data/music_palette.c"
#include "convert/midi_load.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

void process_arguments_musics(ecs_world_t *world, char* args[], int count) {
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--nomusic") == 0) {
            nomusic = 1;
            zox_log("+ setting enabled [nomusic]")
        }
    }
}

zox_begin_module(Musics)
    // Notes
    zox_define_tag(Note)
    zox_define_tag(Music)
    zox_define_tag(Looping)
    // Music
    zox_define_component_byte(MusicNote)
    zox_define_component_byte(GenerateMusic)
    zox_define_component_byte(MusicEnabled)
    zox_define_component_double(MusicTime)
    zox_define_component_double(MusicSpeed)
    zox_define_component_double(MusicLength)
    zox_define_entities_component(NoteLinks)
    // playlist
    zox_define_tag(Playlist)
    zox_define_component_byte(PlaylistEnabled)
    zox_define_component_byte(MusicPlaying)
    zox_define_entities_component(MusicLinks)
    // realm
    zox_define_component_byte(PlaylistPlaying)
    zox_define_component_byte(PlaylistMode)
    zox_define_entities_component(PlaylistLinks)
    zox_define_component_entity(PlaylistLink)
    zox_system_1(MusicGenerateSystem, zox_pip_mainthread,
        [out] GenerateMusic,
        [out] NoteLinks,
        [none] Music)
    zox_system_1(MusicPlaySystem, zox_pip_mainthread,
        [in] MusicEnabled,
        [in] NoteLinks,
        [in] MusicSpeed,
        [out] MusicNote,
        [out] MusicTime,
        [none] Music)
    spawn_prefabs_musics(world);
    add_hook_terminal_command(process_arguments_musics);
zox_end_module(Musics)

#endif
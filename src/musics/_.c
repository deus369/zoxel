#ifndef zoxm_musics
#define zoxm_musics

// todo: make sub modules:
//      - notes
//      - songs
//      - playlists
//      - io

#include "settings/_.c"
#define playlist_mode_loop 0    // stick on same track
#define playlist_mode_cycle 1   // play through list sequentially
#define playlist_mode shuffle 2 // random non repeating track each time
zox_tag(Note);
zox_tag(Music);
zox_tag(Looping);
zoxc_byte(MusicNote);
zoxc_byte(GenerateMusic);
zoxc_byte(MusicEnabled);
zoxc_double(MusicLength);
zoxc_double(MusicTime);
zoxc_double(MusicSpeed);
zoxc_entities(NoteLinks)
// playlist
zox_tag(Playlist);
zoxc_byte(PlaylistEnabled);
zoxc_byte(MusicPlaying);
zoxc_entities(MusicLinks)
// realm
zoxc_byte(PlaylistPlaying);
zoxc_entities(PlaylistLinks)
zoxc_entity(PlaylistLink);
// playlist mode
zoxc_byte(PlaylistMode);

// zoxc_arrayd(MusicData, int);
#include "data/music_palette.c"
#include "convert/midi_load.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

void process_arguments_musics(ecs_world_t *world, char* args[], int count) {
    (void) world;
    for (int i = 1; i < count; i++) {
        if (strcmp(args[i], "--nomusic") == 0) {
            nomusic = 1;
            zox_log("+ setting enabled [nomusic]");
        }
    }
}

void on_boot_musics(ecs_world_t* world, ecs_entity_t app) {
    if (nosounds) {
        zox_logv("Sounds are disabled: no music.");
        return;
    }
    zox_geter_value(app, RealmLink, ecs_entity_t, realm);
    spawn_realm_playlist(world, realm);
}

zox_begin_module(Musics)
    // Notes
    zox_define_tag(Note);
    zox_define_tag(Music);
    zox_define_tag(Looping);
    // Music
    zox_define_component_byte(MusicNote);
    zox_define_component_byte(GenerateMusic);
    zox_define_component_byte(MusicEnabled);
    zox_define_component_double(MusicTime);
    zox_define_component_double(MusicSpeed);
    zox_define_component_double(MusicLength);
    zox_define_entities_component(NoteLinks);
    // playlist
    zox_define_tag(Playlist);
    zox_define_component_byte(PlaylistEnabled);
    zox_define_component_byte(MusicPlaying);
    zox_define_entities_component(MusicLinks);
    // realm
    zox_define_component_byte(PlaylistPlaying);
    zox_define_component_byte(PlaylistMode);
    zox_define_entities_component(PlaylistLinks);
    zox_define_component_entity(PlaylistLink);

    define_systems_music(world);

    add_hook_on_boot(on_boot_musics);;
    add_hook_terminal_command(process_arguments_musics);
    add_hook_spawn_prefabs(spawn_prefabs_musics);
zox_end_module(Musics)

#endif
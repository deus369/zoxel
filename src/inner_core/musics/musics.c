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
zox_declare_tag(Playlist)
zox_component_byte(MusicNote)
zox_component_byte(GenerateMusic)
zox_component_byte(MusicPlaying)
zox_component_double(MusicLength)
zox_component_double(MusicTime)
zox_component_double(MusicSpeed)
zox_entities_component(NoteLinks)
zox_component_byte(PlaylistIndex)
zox_entities_component(MusicLinks)
zox_component_entity(PlaylistLink)
// zox_memory_component(MusicData, int)
#include "util/music_palette.c"
#include "convert/midi_load.c"
#include "prefabs/prefabs.c"
#include "util/playlist.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

void initialize_music(ecs_world_t *world, const ecs_entity_t realm) {
    const ecs_entity_t playlist = spawn_playlist(world, prefab_playlist);
    const ecs_entity_t music_file1 = load_music_file(world, prefab_music_file, prefab_note);
    const ecs_entity_t generated_music = spawn_music_generated(world, prefab_music_generated); // _square
    add_music(world, playlist, music_file1);
    add_music(world, playlist, generated_music);
#ifdef zox_test_music_files
    local_music = music_file1;
    play_music(world, playlist, 0);
#else
    local_music = generated_music;
    play_music(world, playlist, 1);
#endif
    zox_set(local_music, MusicPlaying, { 1 })
    zox_set(realm, PlaylistLink, { playlist })
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
zox_define_component_double(MusicLength)
zox_define_entities_component(NoteLinks)
zox_define_tag(Playlist)
zox_define_component_byte(PlaylistIndex)
zox_define_entities_component(MusicLinks)
zox_define_component_entity(PlaylistLink)
zox_system_1(MusicGenerateSystem, zox_pip_mainthread, [out] GenerateMusic, [out] NoteLinks, [none] Music)
zox_system_1(MusicPlaySystem, zox_pip_mainthread, [in] MusicPlaying, [in] NoteLinks, [in] MusicSpeed, [out] MusicNote, [out] MusicTime, [none] Music)
spawn_prefabs_musics(world);
zox_prefab_set(prefab_realm, PlaylistLink, { 0 })
zoxel_end_module(Musics)

#endif

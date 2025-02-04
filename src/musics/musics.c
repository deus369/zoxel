#ifndef zox_mod_musics
#define zox_mod_musics

#define zox_test_music_files

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
zox_component_entity(PlaylistLink)
zox_entities_component(MusicLinks)
zox_entities_component(PlaylistLinks)

// zox_memory_component(MusicData, int)
#include "util/music_palette.c"
#include "convert/midi_load.c"
#include "prefabs/prefabs.c"
#include "util/playlist.c"
#include "util/game_music.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

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
zox_define_entities_component(PlaylistLinks)
zox_define_component_entity(PlaylistLink)
zox_system_1(MusicGenerateSystem, zox_pip_mainthread, [out] GenerateMusic, [out] NoteLinks, [none] Music)
zox_system_1(MusicPlaySystem, zox_pip_mainthread, [in] MusicPlaying, [in] NoteLinks, [in] MusicSpeed, [out] MusicNote, [out] MusicTime, [none] Music)
spawn_prefabs_musics(world);
zox_prefab_set(prefab_realm, PlaylistLink, { 0 })
zox_prefab_add(prefab_realm, PlaylistLinks)
zoxel_end_module(Musics)

#endif

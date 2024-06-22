#ifndef zox_mod_musics
#define zox_mod_musics

const int music_note_skip = 84;
const float default_music_volume = 2.2f;
zox_declare_tag(Music)
zox_declare_tag(Looping)
zox_component_byte(MusicNote)
zox_component_byte(GenerateMusic)
zox_component_double(MusicTime)
zox_component_double(MusicSpeed)
zox_memory_component(MusicData, int)
#include "util/music_palette.c"
#include "prefabs/prefabs.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

zox_begin_module(Musics)
zox_define_tag(Music)
zox_define_tag(Looping)
zox_define_component_byte(MusicNote)
zox_define_component_byte(GenerateMusic)
zox_define_component_double(MusicTime)
zox_define_component_double(MusicSpeed)
zox_define_memory_component(MusicData)
zox_system(MusicGenerateSystem, EcsPostUpdate, [none] Music, [out] GenerateMusic, [out] MusicData, [out] InstrumentType)
zox_system_1(MusicPlaySystem, main_thread_pipeline, [none] Music, [in] MusicData, [in] MusicSpeed, [in] InstrumentType, [out] MusicNote, [out] MusicTime)
spawn_prefabs_musics(world);
zoxel_end_module(Musics)

#endif

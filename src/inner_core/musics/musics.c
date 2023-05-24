#ifndef zoxel_musics
#define zoxel_musics

zox_declare_tag(Music)
zox_declare_tag(Looping)
zox_component(MusicTime, double)
zox_component(MusicSpeed, double)
zox_memory_component(MusicData, int)
zoxel_byte_component(GenerateMusic)
zox_reset_system(GenerateMusicResetSystem, GenerateMusic)
#include "util/music_palette.c"
#include "prefabs/music.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

zox_begin_module(Musics)
zox_define_tag(Music)
zox_define_tag(Looping)
zox_define_component(GenerateMusic)
zox_define_component(MusicTime)
zox_define_component(MusicSpeed)
zox_define_memory_component(MusicData)
zox_system(MusicGenerateSystem, EcsPostUpdate, [none] Music, [in] GenerateMusic, [out] MusicData, [out] InstrumentType)
zox_system(MusicPlaySystem, EcsOnUpdate, [none] Music, [in] MusicData, [in] MusicSpeed, [in] InstrumentType, [out] MusicTime)
zox_define_reset_system(GenerateMusicResetSystem, GenerateMusic)
spawn_prefab_music(world);
zoxel_end_module(Musics)

//! \todo MusicPlayer -> play a music and pick a new one when song ends
//! \todo MusicData - Contains a bunch of notes? - make custom struct for this with timing + note

#endif
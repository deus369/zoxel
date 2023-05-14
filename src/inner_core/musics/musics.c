#ifndef zoxel_musics
#define zoxel_musics

zoxel_declare_tag(Music)
zoxel_declare_tag(Looping)
zoxel_component(MusicTime, double)
zoxel_component(MusicSpeed, double)
zoxel_memory_component(MusicData, int)
zoxel_byte_component(GenerateMusic)
zox_reset_system(GenerateMusicResetSystem, GenerateMusic)
#include "util/music_palette.c"
#include "prefabs/music.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

zoxel_begin_module(Musics)
zoxel_define_tag(Music)
zoxel_define_tag(Looping)
zoxel_define_component(GenerateMusic)
zoxel_define_component(MusicTime)
zoxel_define_component(MusicSpeed)
zoxel_define_memory_component(MusicData)
zox_system(MusicGenerateSystem, EcsPostUpdate, [none] Music, [in] GenerateMusic, [out] MusicData, [out] InstrumentType)
zox_system(MusicPlaySystem, EcsOnUpdate, [none] Music, [in] MusicData, [in] MusicSpeed, [in] InstrumentType, [out] MusicTime)
zox_define_reset_system(GenerateMusicResetSystem, GenerateMusic)
spawn_prefab_music(world);
zoxel_end_module(Musics)

//! \todo MusicPlayer -> play a music and pick a new one when song ends
//! \todo MusicData - Contains a bunch of notes? - make custom struct for this with timing + note

#endif
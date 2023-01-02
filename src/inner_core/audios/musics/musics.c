#ifndef zoxel_musics
#define zoxel_musics

zoxel_declare_tag(Music)
zoxel_declare_tag(Looping)
zoxel_component(MusicTime, double)
zoxel_memory_component(MusicData, int)      //! Contains a bunch of notes? - make custom struct for this with timing + note
zoxel_state_component(GenerateMusic)
zoxel_reset_system(GenerateMusicResetSystem, GenerateMusic)
#include "prefabs/music.c"
#include "systems/music_play_system.c"
#include "systems/music_generate_system.c"

//! Musics Module.
void MusicsImport(ecs_world_t *world)
{
    zoxel_module(Musics)
    zoxel_define_tag(Music)
    zoxel_define_tag(Looping)
    zoxel_define_component(GenerateMusic)
    zoxel_define_component(MusicTime)
    zoxel_memory_component_define(world, MusicData)
    zoxel_system(world, MusicGenerateSystem, EcsOnUpdate,
        [none] Music, [in] GenerateMusic, [out] MusicData)
    zoxel_system(world, MusicPlaySystem, EcsOnLoad,
        [none] Music, [in] MusicData, [out] MusicTime)
    zoxel_reset_system_define(GenerateMusicResetSystem, GenerateMusic)
    spawn_prefab_music(world);
    // test
    spawn_music(world);
}
#endif
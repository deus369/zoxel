#ifndef Zoxel_Audios
#define Zoxel_Audios

#include "Sounds/Sounds.c"
#include "Musics/Musics.c"

//! Textures Module.
void AudiosImport(ecs_world_t *world)
{
    ECS_MODULE(world, Audios);
    ECS_IMPORT(world, Sounds);
    ECS_IMPORT(world, Musics);
}
#endif
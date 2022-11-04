#ifndef zoxel_audios
#define zoxel_audios

#include "sounds/sounds.c"
#include "musics/musics.c"

//! textures Module.
void AudiosImport(ecs_world_t *world)
{
    ECS_MODULE(world, Audios);
    ECS_IMPORT(world, Sounds);
    ECS_IMPORT(world, Musics);
}
#endif
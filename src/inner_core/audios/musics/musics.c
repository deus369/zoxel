#ifndef zoxel_musics
#define zoxel_musics

// Tags
ECS_DECLARE(Music);
// components

//! Musics Module.
void MusicsImport(ecs_world_t *world)
{
    zoxel_module(Musics)
    ECS_TAG_DEFINE(world, Music);
    // components

    // systems
    
    // prefabs
    // SpawnSoundPrefab(world);
}
#endif
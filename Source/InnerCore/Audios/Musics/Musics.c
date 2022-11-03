#ifndef Zoxel_Musics
#define Zoxel_Musics

// Tags
ECS_DECLARE(Music);
// Components

//! Musics Module.
void MusicsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Musics);
    ECS_TAG_DEFINE(world, Music);
    // Components

    // Systems
    
    // Prefabs
    // SpawnSoundPrefab(world);
}
#endif
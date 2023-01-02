#ifndef zoxel_gameplay
#define zoxel_gameplay

#include "characters/characters.c"

void GameplayImport(ecs_world_t *world)
{
    zoxel_module(Gameplay)
    zoxel_import_module(Characters)
}
#endif
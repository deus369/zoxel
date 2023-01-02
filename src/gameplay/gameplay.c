#ifndef zoxel_gameplay
#define zoxel_gameplay

// --- Space ---
#include "characters/characters.c"

void GameplayImport(ecs_world_t *world)
{
    zoxel_module(Gameplay)
    ECS_IMPORT(world, Characters);
}
#endif
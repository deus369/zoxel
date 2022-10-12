#ifndef Zoxel_Players
#define Zoxel_Players

#include "Tags/Bob.c"
ECS_COMPONENT_DECLARE(Bob);
#include "Systems/BobSpawnSystem.c"
#include "Systems/BobMoveSystem.c"

void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    // ECS_COMPONENT_DEFINE(world, Bob);
    ECS_TAG(world, Bob);
    ECS_SYSTEM(world, BobSpawnSystem, EcsOnUpdate, Keyboard);
    ECS_SYSTEM(world, BobMoveSystem, EcsOnUpdate, Keyboard, Bob());
}

void PostInitializePlayers(ecs_world_t *world)
{
    InitializeBobSpawnSystem(world);
    SpawnPlayer(world);
}

#endif
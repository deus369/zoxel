#ifndef Zoxel_Players
#define Zoxel_Players
//! Players Module
/**
 * \todo Use ECS_SYSTEM_DEFINE & DECLARE for MoveSystem, why does it crash?
 * \todo Spawning Queries in Initialize function as they depend on other Modules.
*/
// you can assign anything to ctx, make a struct with multiple queries for injection ecs_id(BobMoveSystem), 

// Tags
ECS_DECLARE(Player);
ECS_DECLARE(Player2D);
ECS_DECLARE(DisableMovement);
// Systems
#include "Systems/BobSpawnSystem.c"
#include "Systems/BobMoveSystem.c"

void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    ECS_TAG_DEFINE(world, Player);
    ECS_TAG_DEFINE(world, Player2D);
    ECS_TAG_DEFINE(world, DisableMovement);
    // ECS_SYSTEM(world, BobMoveSystem, EcsOnUpdate, Keyboard);
    ECS_SYSTEM_DEFINE(world, BobSpawnSystem, EcsOnUpdate, Keyboard);
    ECS_SYSTEM_DEFINE(world, BobMoveSystem, EcsOnUpdate, Keyboard);
}

void InitializePlayers(ecs_world_t *world)
{
    InitializeBobSpawnSystem(world);
    #ifdef Zoxel_Physics2D
    ecs_query_t *bobQuery = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            { ecs_id(Player2D) },
            { ecs_id(Acceleration2D) }
        }
    });
    ecs_system(world, {
        .entity = ecs_id(BobSpawnSystem),
        .no_staging = true
    });
    ecs_system(world, {
        .entity = ecs_id(BobMoveSystem),
        .ctx = bobQuery
    });
    #endif
}

#endif
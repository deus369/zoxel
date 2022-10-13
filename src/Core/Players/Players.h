#ifndef Zoxel_Players
#define Zoxel_Players

// you can assign anything to ctx, make a struct with multiple queries for injection

ECS_DECLARE(Bob);

#include "Systems/BobSpawnSystem.c"
#include "Systems/BobMoveSystem.c"
ECS_SYSTEM_DECLARE(BobSpawnSystem);
// ECS_SYSTEM_DECLARE(BobMoveSystem);

void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    ECS_TAG_DEFINE(world, Bob);
    ECS_SYSTEM_DEFINE(world, BobSpawnSystem, EcsOnUpdate, Keyboard);
    // ECS_SYSTEM_DEFINE(world, BobMoveSystem, EcsOnUpdate, Keyboard); // , Bob());
    ECS_SYSTEM(world, BobMoveSystem, EcsOnUpdate, Keyboard); // , Bob());
    ecs_query_t *bobQuery = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {
            { ecs_id(Bob) },
            { ecs_id(Acceleration2D) }
        }
    });
    ecs_system(world, { .entity = BobMoveSystem, .ctx = bobQuery });
    printf("Bob ID %lu\n", ecs_id(Bob));
    printf("Acceleration2D ID %lu\n", ecs_id(Acceleration2D));
}

void PostInitializePlayers(ecs_world_t *world)
{
    InitializeBobSpawnSystem(world);
    SpawnPlayer(world);
    /*bobQuery = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {
            { ecs_id(Bob) }
            // { ecs_id(Velocity2D) }
        }
    });
    ecs_system(world, { .entity = BobMoveSystem, .ctx = bobQuery });*/
}

// { .id = ecs_id(Bob) } 
// { .id = ecs_id(Velocity2D), .inout = EcsIn}
/*ecs_query_t *bobQuery = ecs_query(world, {
    .filter.terms = {
        { .id = ecs_id(Velocity2D) }
        // { .id = ecs_id(Bob) }
    }
});*/

#endif
#ifndef Zoxel_Players
#define Zoxel_Players
//! Players Module
/**
 * \todo Spawning Queries in Initialize function as they depend on other Modules.
*/
// you can assign anything to ctx, make a struct with multiple queries for injection ecs_id(Player2DMoveSystem), 

// Tags
ECS_DECLARE(Player);
ECS_DECLARE(Player2D);
ECS_DECLARE(PlayerCharacter2D);
ECS_DECLARE(DisableMovement);
// Systems
#include "Systems/Player2DMoveSystem.c"
#include "Systems/Player2DTestSystem.c"
#include "Systems/CameraMoveSystem.c"
// prefabs
ecs_entity_t playerCharacter2DPrefab;

//! Spawn a Player character.
ecs_entity_t SpawnPlayerCharacter2D(ecs_world_t *world)
{
    // child prefabs don't seem to inherit tags
    ecs_entity_t bobPlayer = ecs_new_w_pair(world, EcsIsA, playerCharacter2DPrefab);
    ecs_set(world, bobPlayer, Scale2D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, bobPlayer, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    printf("Spawned Player2D [%lu]\n", (long unsigned int) bobPlayer);
    return bobPlayer;
}

//! Initializes prefabs for bob.
void SpawnPlayerCharacter2DPrefab(ecs_world_t *world)
{
    playerCharacter2DPrefab = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    ecs_add_id(world, playerCharacter2DPrefab, EcsPrefab);
    ecs_set_name(world, playerCharacter2DPrefab, "PlayerCharacter2D2");
    ecs_add(world, playerCharacter2DPrefab, PlayerCharacter2D);
}

void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    ECS_TAG_DEFINE(world, Player);
    ECS_TAG_DEFINE(world, Player2D);
    ECS_TAG_DEFINE(world, PlayerCharacter2D);
    ECS_TAG_DEFINE(world, DisableMovement);
    ZOXEL_SYSTEM_MULTITHREADED(world, Player2DMoveSystem, EcsOnUpdate, [in] Keyboard);
    ECS_SYSTEM_DEFINE(world, Player2DTestSystem, EcsOnUpdate, [in] Keyboard);
    SpawnPlayerCharacter2DPrefab(world);
    #ifdef Zoxel_Physics2D
    // \todo Add in out tags to this filter
    ecs_query_t *bobQuery = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            { ecs_id(PlayerCharacter2D) },
            { ecs_id(Acceleration2D) },
            { ecs_id(Velocity2D) }
        }
    });
    ecs_system(world, {
        .entity = ecs_id(Player2DMoveSystem),
        .ctx = bobQuery
    });
    #endif
    //#if Zoxel_Particles2D
    ECS_SYSTEM_DEFINE(world, Player2DTestSystem, EcsOnUpdate, [in] Keyboard);
    ecs_system(world, {
        .entity = ecs_id(Player2DTestSystem),
        // rename to no_readonly
        .no_staging = true  // with structural changes, does it at the end of the process..
    });
    //#endif
    ZOXEL_SYSTEM_MULTITHREADED(world, CameraMoveSystem, EcsOnUpdate, [in] Keyboard);
    ecs_query_t *cameraQuery = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            { ecs_id(Camera) },
            { ecs_id(Position) },
            { ecs_id(Rotation) },
           // { ecs_id(Velocity2D) }
        }
    });
    ecs_system(world, {
        .entity = ecs_id(CameraMoveSystem),
        .ctx = cameraQuery
    });
}

// EcsOnDeleteTarget use this
// ecs_entity_t SpawnPlayerCharacter2D(ecs_world_t *world);
#endif
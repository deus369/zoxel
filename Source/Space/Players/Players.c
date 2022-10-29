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
#include "Systems/CameraFollow2DSystem.c"
// prefabs
#include "Prefabs/PlayerCharacter2D.c"

//! Spawn a Player character.
ecs_entity_t SpawnPlayerCharacter2D(ecs_world_t *world)
{
    // child prefabs don't seem to inherit tags
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, playerCharacter2DPrefab);
    ecs_set(world, e, Scale2D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    printf("Spawned Player2D [%lu]\n", (long unsigned int) e);
    SpawnGPUMaterial(world, e);
    SpawnGPUTexture(world, e);
    return e;
}

// Why can't i use Cameras.CameraFollower2D tag instead?
ECS_DECLARE(CameraFollower2D);

void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    ECS_TAG_DEFINE(world, Player);
    ECS_TAG_DEFINE(world, Player2D);
    ECS_TAG_DEFINE(world, PlayerCharacter2D);
    ECS_TAG_DEFINE(world, DisableMovement);
    ECS_TAG_DEFINE(world, CameraFollower2D);
    ecs_add(world, cameraPrefab, CameraFollower2D);
    // ECS_ENTITY_DEFINE(world, Camera, 0);
    // printf("Camera ECS ID [%lu]\n", (long unsigned int) ecs_id(Camera));
    // ECS_SYSTEM_DEFINE(world, CameraFollow2DSystem, EcsOnUpdate, [none] Camera, [out] Position);

    #ifdef Zoxel_Physics2D
    // ECS_SYSTEM_DEFINE(world, CameraFollow2DSystem, EcsOnUpdate, [none] Camera, [out] Position);
    ZOXEL_SYSTEM_MULTITHREADED(world, CameraFollow2DSystem, EcsOnUpdate, [none] CameraFollower2D, [out] Position);
    ecs_query_t *playerCharacter2DQuery = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            { ecs_id(PlayerCharacter2D), .inout = EcsInOutNone },
            { ecs_id(Position2D), .inout = EcsIn }
        }
    });
    ecs_system(world, {
        .entity = ecs_id(CameraFollow2DSystem),
        .ctx = playerCharacter2DQuery
    });
    // \todo Add in out tags to this filter
    ZOXEL_SYSTEM_MULTITHREADED(world, Player2DMoveSystem, EcsOnUpdate, [in] Keyboard);
    ecs_query_t *playerCharacter2DQuery2 = ecs_query_init(world, &(ecs_query_desc_t) {
        .filter.terms = {
            { ecs_id(PlayerCharacter2D), .inout = EcsInOutNone },
            { ecs_id(Acceleration2D), .inout = EcsOut },
            { ecs_id(Velocity2D), .inout = EcsIn }
        }
    });
    ecs_system(world, {
        .entity = ecs_id(Player2DMoveSystem),
        .ctx = playerCharacter2DQuery2
    });
    #endif
    //#if Zoxel_Particles2D
    ECS_SYSTEM_DEFINE(world, Player2DTestSystem, EcsOnUpdate, [in] Keyboard);
    ecs_system(world, {
        .entity = ecs_id(Player2DTestSystem),
        .no_staging = true  // rename to no_readonly - with structural changes, does it at the end of the process..
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
    // Prefabs
    InitializePlayerCharacter2DPrefab(world);
}

// EcsOnDeleteTarget use this
// ecs_entity_t SpawnPlayerCharacter2D(ecs_world_t *world);
#endif
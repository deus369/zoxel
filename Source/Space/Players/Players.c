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
ZOXEL_COMPONENT(CameraFree, bool);
// Systems
#include "Systems/Player2DMoveSystem.c"
#include "Systems/Player2DTestSystem.c"
#include "Systems/CameraFollow2DSystem.c"
#include "Systems/CameraMoveSystem.c"
#include "Systems/CameraRotateSystem.c"
// prefabs
#include "Prefabs/PlayerCharacter2D.c"

//! Spawn a Player character.
ecs_entity_t SpawnPlayerCharacter2D(ecs_world_t *world)
{
    // child prefabs don't seem to inherit tags
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, playerCharacter2DPrefab);
    ecs_set(world, e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    printf("Spawned Player2D [%lu]\n", (long unsigned int) e);
    SpawnGPUMaterial(world, e);
    SpawnGPUTexture(world, e);
    return e;
}

// ECS_DECLARE(CameraFollower2D);  // Why can't i use Cameras.CameraFollower2D tag instead?
void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    // Tags
    ECS_TAG_DEFINE(world, Player);
    ECS_TAG_DEFINE(world, Player2D);
    ECS_TAG_DEFINE(world, PlayerCharacter2D);
    ECS_TAG_DEFINE(world, DisableMovement);
    // Systems
    #ifdef Zoxel_Physics2D
    // ECS_SYSTEM_DEFINE(world, CameraFollow2DSystem, EcsOnUpdate, [none] Camera, [out] Position);
    ZOXEL_FILTER(playerCharacter2DQuery, world, [none] PlayerCharacter2D, [in] Position2D);
    ZOXEL_SYSTEM_MULTITHREADED_CTX(world, CameraFollow2DSystem, EcsOnUpdate, playerCharacter2DQuery, [none] cameras.CameraFollower2D, [out] Position);
    // \todo Add in out tags to this filter
    ZOXEL_FILTER(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D);
    ZOXEL_SYSTEM_MULTITHREADED_CTX(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
    #endif
    ZOXEL_FILTER(cameraQuery, world, [none] cameras.Camera, [out] Position, [out] Rotation);
    ZOXEL_SYSTEM_MULTITHREADED_CTX(world, CameraMoveSystem, EcsOnUpdate, cameraQuery, [in] Keyboard);
    ZOXEL_FILTER(cameraQuery2, world, [none] cameras.Camera, [out] Rotation);
    ZOXEL_SYSTEM_MULTITHREADED_CTX(world, CameraRotateSystem, EcsOnUpdate, cameraQuery2, [in] Mouse);
    //#if Zoxel_Particles2D
    ECS_SYSTEM_DEFINE(world, Player2DTestSystem, EcsOnUpdate, [in] Keyboard);
    //! Needed for bulk spawning. Still crashes.
    ecs_system(world, {
        .entity = ecs_id(Player2DTestSystem),
        .no_staging = true
    });
    //#endif
    // Prefabs
    InitializePlayerCharacter2DPrefab(world);
}
#endif
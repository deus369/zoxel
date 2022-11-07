#ifndef zoxel_players
#define zoxel_players
//! players Module
/**
 * \todo Spawning Queries in Initialize function as they depend on other Modules.
*/
// you can assign anything to ctx, make a struct with multiple queries for injection ecs_id(Player2DMoveSystem), 

// Tags
ECS_DECLARE(Player);
ECS_DECLARE(Player2D);
ECS_DECLARE(PlayerCharacter2D);
// systems
#include "systems/Player2DMoveSystem.c"
#include "systems/Player2DTestSystem.c"
#include "systems/CameraFollow2DSystem.c"
#include "systems/FreeCameraMoveSystem.c"
#include "systems/FreeCameraRotateSystem.c"
#include "systems/FreeCameraToggleSystem.c"
// prefabs
#include "prefabs/player_character2D.c"
// util
#include "util/player_character2D.c"

// ECS_DECLARE(CameraFollower2D);  // Why can't i use cameras.CameraFollower2D tag instead?
void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    // Tags
    ECS_TAG_DEFINE(world, Player);
    ECS_TAG_DEFINE(world, Player2D);
    ECS_TAG_DEFINE(world, PlayerCharacter2D);
    // prefabs
    spawn_player_character2D_prefab(world);
    // systems
    #ifdef zoxel_physics2D
    // ECS_SYSTEM_DEFINE(world, CameraFollow2DSystem, EcsOnUpdate, [none] Camera, [out] Position);
    // printf("Character2DLink %s", ecs_get_fullpath(world, Character2DLink));
    // printf("Character2DLink %s", ecs_get_fullpath(world, ecs_id(Character2DLink)));
    // zoxel_filter(playerCharacter2DQuery, world, [none] PlayerCharacter2D, [in] Position2D);
    zoxel_system(world, CameraFollow2DSystem, EcsOnUpdate, // playerCharacter2DQuery,
        [none] cameras.CameraFollower2D, [in] cameras.FreeRoam, [in] characters2.d.Character2DLink, [out] Position, [out] Rotation);
    // \todo Add in out tags to this filter
    zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D, [in] physics.DisableMovement);
    zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
    #endif
    zoxel_filter(cameraQuery, world, [none] cameras.Camera, [in] cameras.FreeRoam, [out] Position, [out] Rotation);
    zoxel_system_ctx(world, FreeCameraMoveSystem, EcsOnUpdate, cameraQuery, [in] Keyboard);
    zoxel_filter(cameraQuery2, world, [none] cameras.Camera, [out] Rotation, [out] Euler, [in] cameras.FreeRoam);
    zoxel_system_ctx(world, FreeCameraRotateSystem, EcsOnUpdate, cameraQuery2, [in] Mouse);
    zoxel_filter(cameraQuery3, world, [none] cameras.Camera, [out] cameras.FreeRoam);
    zoxel_filter(playerCharacter2DQuery3, world, [none] PlayerCharacter2D, [out] physics.DisableMovement);
    zoxel_system_ctx(world, FreeCameraToggleSystem, EcsOnUpdate, cameraQuery3, [in] Mouse);
    zoxel_system_ctx(world, FreeCameraDisableMovementSystem, EcsOnUpdate, playerCharacter2DQuery3, [in] Mouse);
    //#if zoxel_particles2D
    ECS_SYSTEM_DEFINE(world, Player2DTestSystem, EcsOnUpdate, [in] Keyboard);
    //! Needed for bulk spawning. Still crashes.
    ecs_system(world, {
        .entity = ecs_id(Player2DTestSystem),
        .no_readonly = true // no_staging - rename to no_readonly
    });
    //#endif
}
#endif
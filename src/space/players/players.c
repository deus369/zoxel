#ifndef zoxel_players
#define zoxel_players

ecs_entity_t local_player;
// Tags
ECS_DECLARE(Player2D);
ECS_DECLARE(Player3D);
ECS_DECLARE(PlayerCharacter);
ECS_DECLARE(PlayerCharacter2D);
ECS_DECLARE(PlayerCharacter3D);
// prefabs
#include "prefabs/player_character2D.c"
#include "prefabs/player_character3D.c"
// util
#include "util/player_character2D.c"
#include "util/player_character3D.c"
// systems
#include "systems/player2D_move_system.c"
#include "systems/player2D_test_system.c"
#include "systems/player3D_move_system.c"
#include "systems/free_camera_move_system.c"
#include "systems/free_camera_rotate_system.c"
#include "systems/free_camera_toggle_system.c"

//! players Module
/**
 * \todo Spawning Queries in Initialize function as they depend on other Modules.
*/
void PlayersImport(ecs_world_t *world)
{
    ECS_MODULE(world, Players);
    ECS_TAG_DEFINE(world, Player2D);
    ECS_TAG_DEFINE(world, Player3D);
    ECS_TAG_DEFINE(world, PlayerCharacter);
    ECS_TAG_DEFINE(world, PlayerCharacter2D);
    ECS_TAG_DEFINE(world, PlayerCharacter3D);
    spawn_player_character2D_prefab(world);
    spawn_player_character3D_prefab(world);
    #ifdef zoxel_physics2D
    zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D,
        [in] physics.DisableMovement);
    zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
    #endif
    #ifdef zoxel_physics3D
    zoxel_filter(playerCharacter3DQuery, world, [none] PlayerCharacter3D, [out] Acceleration3D, [in] Velocity3D,
        [in] physics.DisableMovement);
    zoxel_system_ctx(world, Player3DMoveSystem, EcsOnUpdate, playerCharacter3DQuery, [in] Keyboard);
    #endif
    zoxel_filter(cameraQuery, world, [none] cameras.Camera, [in] cameras.FreeRoam, [out] Position, [out] Rotation);
    zoxel_system_ctx(world, FreeCameraMoveSystem, EcsOnUpdate, cameraQuery, [in] Keyboard);
    zoxel_filter(cameraQuery2, world, [none] cameras.Camera, [in] cameras.FreeRoam, [out] Euler);
    zoxel_system_ctx(world, FreeCameraRotateSystem, EcsOnUpdate, cameraQuery2, [in] Mouse);
    zoxel_filter(cameraQuery3, world, [none] cameras.Camera, [out] cameras.FreeRoam);
    zoxel_filter(playerCharacter2DQuery3, world, [none] PlayerCharacter, [out] physics.DisableMovement);
    zoxel_system_ctx(world, FreeCameraToggleSystem, EcsOnUpdate, cameraQuery3, [in] Mouse);
    zoxel_system_ctx(world, FreeCameraDisableMovementSystem, EcsOnUpdate, playerCharacter2DQuery3, [in] Mouse);
    //#if zoxel_particles2D
    //! Needed for bulk spawning. Still crashes.
    ECS_SYSTEM_DEFINE(world, Player2DTestSystem, EcsOnUpdate, [in] Keyboard);
    ecs_system(world, {
        .entity = ecs_id(Player2DTestSystem),
        .no_readonly = true // no_staging - rename to no_readonly
    });
    // this has to update after reset systems (as gen is stuck on main thread, running before everything)
    zoxel_system(world, Player2DTestMainThreadSystem, EcsOnStore, [in] Keyboard);
}
#endif
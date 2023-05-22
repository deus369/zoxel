#ifndef zoxel_players
#define zoxel_players

zoxel_declare_tag(Player)
zoxel_declare_tag(Player2D)
zoxel_declare_tag(Player3D)
zoxel_declare_tag(PlayerCharacter)
zoxel_declare_tag(PlayerCharacter2D)
zoxel_declare_tag(PlayerCharacter3D)
ecs_entity_t local_player;
#include "prefabs/player.c"
#include "prefabs/player_character2D.c"
#include "prefabs/player_character3D.c"
#include "util/player_character2D.c"
#include "util/player_character3D.c"
#include "util/attach3D.c"
#include "systems/player2D_move_system.c"
#include "systems/player2D_test_system.c"
#include "systems/player3D_move_system.c"
#include "systems/player3D_rotate_system.c"
#include "systems/free_camera_move_system.c"
#include "systems/free_camera_rotate_system.c"
#include "systems/free_camera_toggle_system.c"
#include "systems/free_camera_disable_movement_system.c"
#include "systems/player_pause_system.c"
#include "systems/player_start_system.c"
#include "systems/device_mode_response_system.c"

zoxel_begin_module(Players)
zoxel_define_tag(Player)
zoxel_define_tag(Player2D)
zoxel_define_tag(Player3D)
zoxel_define_tag(PlayerCharacter)
zoxel_define_tag(PlayerCharacter2D)
zoxel_define_tag(PlayerCharacter3D)
spawn_prefab_player(world);
spawn_player_character2D_prefab(world);
spawn_player_character3D_prefab(world);
#ifdef zoxel_physics2D
    zox_filter(playerCharacter2DQuery2, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D, [in] physics.DisableMovement)
    zox_system_ctx(Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard)
#endif
#ifdef zoxel_physics3D
    zox_filter(player_character3Ds2, [none] PlayerCharacter3D, [out] Acceleration3D, [in] Velocity3D, [in] physics.DisableMovement, [in] Rotation3D)
    zox_filter(playerCharacter3DQuery2, [none] PlayerCharacter3D, [out] Alpha3D, [in] Omega3D, [in] physics.DisableMovement)
    // zox_filter(gamepad_query, [in] Gamepad)
    zox_system_ctx(Player3DMoveSystem, EcsOnUpdate, player_character3Ds2, [none] Player, [in] DeviceLinks)
    zox_system_ctx(Player3DRotateSystem, EcsOnUpdate, playerCharacter3DQuery2, [none] Player, [in] DeviceLinks)
#endif
zox_filter(cameras, [none] cameras.Camera, [in] cameras.FreeRoam, [out] Position3D, [out] Rotation3D)
zox_system_ctx(FreeCameraMoveSystem, EcsOnUpdate, cameras, [in] Keyboard)
zox_filter(cameras2, [none] cameras.Camera, [in] cameras.FreeRoam,
#ifndef zoxel_quaternion_camera
    [out] Euler)
#else
    [out] Rotation3D)
#endif
zox_filter(free_roam_cameras, [none] cameras.Camera, [out] cameras.FreeRoam, [none] !cameras.FirstPersonCamera)
zox_filter(player_character3Ds, [none] PlayerCharacter, [out] physics.DisableMovement)
zox_system_ctx(FreeCameraRotateSystem, EcsOnUpdate, cameras2, [in] Mouse)
zox_system_ctx(FreeCameraToggleSystem, EcsOnUpdate, free_roam_cameras, [in] Mouse, [out] MouseLock)
zox_system_ctx(FreeCameraDisableMovementSystem, EcsOnUpdate, player_character3Ds, [in] Mouse)
zox_system(Player2DTestSystem, EcsOnUpdate, [in] Keyboard)
zox_system(Player2DTestMainThreadSystem, EcsOnStore, [in] Keyboard)
zox_system(PlayerPauseSystem, EcsOnUpdate, [out] Player, [in] DeviceLinks)
{
    zox_system_1(DeviceModeResponseSystem, EcsOnUpdate, [in] DeviceMode)
}
zoxel_end_module(Players)

//#if zoxel_particles2D
//! Needed for bulk spawning. Still crashes.
// \todo Spawning Queries in Initialize function as they depend on other Modules
// zox_system_1(Player2DTestSystem, EcsOnUpdate, [in] Keyboard)
// ecs_system(world, { .entity = ecs_id(Player2DTestSystem), .no_readonly = 1 });
// this has to update after reset systems (as gen is stuck on main thread, running before everything)

#endif
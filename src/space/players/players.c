#ifndef zoxel_players
#define zoxel_players

zox_declare_tag(Player)
zox_declare_tag(Player2D)
zox_declare_tag(PlayerCharacter)
zox_declare_tag(PlayerCharacter2D)
#include "prefabs/player.c"
#include "prefabs/player_character2D.c"
#include "util/player_character2D.c"
#include "util/pause_util.c"
#include "systems/player2D_move_system.c"
#include "systems/free_camera_move_system.c"
#include "systems/free_camera_rotate_system.c"
#include "systems/free_camera_toggle_system.c"
#include "systems/free_camera_disable_movement_system.c"
#include "systems/player_pause_system.c"
#include "systems/device_mode_response_system.c"
#include "players3D/players3D.c"
#include "systems/player2D_test_system.c"
#include "systems/player_shortcuts_system.c"

void spawn_prefabs_players(ecs_world_t *world) {
    spawn_prefab_player(world);
    spawn_player_character2D_prefab(world);
    spawn_prefabs_players3D(world);
}

zox_begin_module(Players)
zox_define_tag(Player)
zox_define_tag(Player2D)
zox_define_tag(PlayerCharacter)
zox_define_tag(PlayerCharacter2D)
#ifdef zoxel_physics2D
    zox_filter(playerCharacter2DQuery2, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D, [in] physics.DisableMovement)
#endif
zox_filter(cameras, [none] cameras.Camera, [in] cameras.FreeRoam, [out] Position3D, [out] Rotation3D)
#ifdef zox_test_quaternion_camera
    zox_filter(cameras2, [none] cameras.Camera, [in] cameras.FreeRoam,[out] Rotation3D)
#else
    zox_filter(cameras2, [none] cameras.Camera, [in] cameras.FreeRoam,[out] Euler)
#endif
zox_filter(free_roam_cameras, [none] cameras.Camera, [out] cameras.FreeRoam, [none] !cameras.FirstPersonCamera)
zox_filter(player_character3Ds, [none] PlayerCharacter, [out] physics.DisableMovement)
#ifdef zoxel_physics2D
    zox_system_ctx(Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard)
#endif
zox_system_ctx(FreeCameraMoveSystem, EcsOnUpdate, cameras, [in] Keyboard)
zox_system_ctx(FreeCameraRotateSystem, EcsOnUpdate, cameras2, [in] Mouse)
// zox_system_ctx(FreeCameraToggleSystem, EcsOnUpdate, free_roam_cameras, [in] Mouse, [out] MouseLock)
zox_system_ctx(FreeCameraDisableMovementSystem, EcsOnUpdate, player_character3Ds, [in] Mouse)
zox_system(Player2DTestSystem, EcsOnUpdate, [in] Keyboard)
zox_system(DeviceModeResponseSystem, EcsOnUpdate, [in] DeviceMode, [in] DeviceModeDirty)
zox_system(PlayerShortcutsSystem, EcsPostUpdate, [none] Player, [in] DeviceLinks)
zox_import_module(Players3D)
// todo: make this work in threading... worked in 3.1.3 - EcsPreStore | EcsOnUpdate
zox_system_1(PlayerShortcutsSingleSystem, main_thread_pipeline, [none] Player, [in] DeviceLinks)
zox_system_1(PlayerPauseSystem, main_thread_pipeline, [none] Player, [in] DeviceLinks)
zoxel_end_module(Players)

#endif
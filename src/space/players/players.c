#ifndef zoxel_players
#define zoxel_players

zox_declare_tag(Player)
zox_declare_tag(Player2D)
zox_declare_tag(Player3D)
zox_declare_tag(PlayerCharacter)
zox_declare_tag(PlayerCharacter2D)
zox_declare_tag(PlayerCharacter3D)
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
#include "systems/player3D_jump_system.c"
#include "systems/device_mode_response_system.c"
#include "systems/player_shortcuts_system.c"

zox_begin_module(Players)
zox_define_tag(Player)
zox_define_tag(Player2D)
zox_define_tag(Player3D)
zox_define_tag(PlayerCharacter)
zox_define_tag(PlayerCharacter2D)
zox_define_tag(PlayerCharacter3D)
spawn_prefab_player(world);
spawn_player_character2D_prefab(world);
spawn_player_character3D_prefab(world);
#ifdef zoxel_physics2D
    zox_filter(playerCharacter2DQuery2, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D, [in] physics.DisableMovement)
    zox_system_ctx(Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard)
#endif
#ifdef zoxel_physics3D
    zox_filter(player_characters, [none] PlayerCharacter3D, [out] Acceleration3D, [in] Velocity3D, [in] physics.DisableMovement, [in] Rotation3D)
    zox_filter(player_characters2, [none] PlayerCharacter3D, [out] Alpha3D, [in] Omega3D, [in] physics.DisableMovement)
    zox_system_ctx(Player3DMoveSystem, EcsOnUpdate, player_characters, [none] Player, [in] DeviceLinks, [in] CharacterLink)
    zox_system_ctx(Player3DRotateSystem, EcsOnUpdate, player_characters2, [none] Player, [in] DeviceLinks)
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
zox_system(PlayerPauseSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks)
zox_system(Player3DJumpSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks, [in] CharacterLink)
zox_system(DeviceModeResponseSystem, EcsOnUpdate, [in] DeviceMode, [in] DeviceModeDirty)
zox_system(PlayerShortcutsSystem, EcsOnStore, [none] Player, [in] DeviceLinks)
zoxel_end_module(Players)

#endif
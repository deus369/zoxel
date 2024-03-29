#ifndef zoxel_players
#define zoxel_players

// zoxel_component_declares
zox_declare_tag(Player)
zox_declare_tag(PlayerCharacter)
zox_component_byte(PlayerState)
zox_memory_component(PlayerLinks, ecs_entity_t)
// zoxel_state_includes
#include "states/player_state.c"
// zoxel_prefab_includes
#include "prefabs/player.c"
// zoxel_util_includes
#include "util/pause_util.c"
#include "util/editor_util.c"
#include "util/player_util.c"
// zoxel_system_includes
#include "systems/free_camera_move_system.c"
#include "systems/free_camera_rotate_system.c"
#include "systems/free_camera_toggle_system.c"
#include "systems/free_camera_disable_movement_system.c"
#include "systems/player_pause_system.c"
#include "systems/device_mode_response_system.c"
#include "systems/virtual_joystick_system.c"
#include "systems/editor_input_system.c"
// zoxel_module_includes
#include "players3D/players3D.c"
#include "players2D/players2D.c"
#include "systems/player2D_test_system.c"
#include "systems/player_shortcuts_system.c"
#include "systems/player_toggle_camera_system.c"

void initialize_players(ecs_world_t *world) {
    add_to_event_start_game((zox_game_event) { &play_game_players });
}

void spawn_prefabs_players(ecs_world_t *world) {
    spawn_prefab_player(world);
    spawn_prefabs_players2D(world);
    spawn_prefabs_players3D(world);
}

zox_begin_module(Players)
// zoxel_component_defines
zox_define_tag(Player)
zox_define_tag(PlayerCharacter)
zox_define_component_byte(PlayerState)
zox_define_memory_component(PlayerLinks)
// zoxel_system_defines
zox_system(FreeCameraMoveSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks, [in] cameras.CameraLink)
zox_system(FreeCameraRotateSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks, [in] cameras.CameraLink)
zox_system(FreeCameraToggleSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks, [in] cameras.CameraLink)
zox_system(PlayerMoreShortcutsSystem, EcsOnUpdate, [in] Keyboard)
zox_system(PlayerShortcutsSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks)
zox_import_module(Players2D)
zox_import_module(Players3D)
zox_system_1(DeviceModeResponseSystem, EcsPreStore, [in] DeviceMode, [in] DeviceModeDirty) // has to update before DeviceModeDirtySystem
zox_system(PlayerToggleCameraSystem, EcsOnUpdate, [none] Player, [in] DeviceLinks, [in] CharacterLink)
zox_system_1(PlayerShortcutsSingleSystem, main_thread_pipeline, [none] Player, [in] DeviceLinks)
zox_system_1(PlayerPauseSystem, main_thread_pipeline, [none] Player, [in] DeviceLinks)
zox_system_1(VirtualJoystickSystem, main_thread_pipeline, [none] Player, [in] DeviceLinks, [in] DeviceMode, [in] RaycasterResult)
zox_system_1(EditorInputSystem, main_thread_pipeline, [none] Player, [in] DeviceLinks)
zoxel_end_module(Players)

#endif

// todo: make this work in threading... worked in 3.1.3 - EcsPreStore | EcsOnUpdate

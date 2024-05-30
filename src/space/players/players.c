#if !defined(zox_mod_players2) && defined(zox_mod_characters)
#define zox_mod_players2

// alot of systems here are actually controller ones, player + device + camera / character, or game states like pause system?
zox_component_entity(PlayerPauseEvent)
#include "data/settings.c"
#include "states/player_state.c"
#include "prefabs/player.c"
#include "util/crosshair.c"
#include "players3D/players3D.c"
#include "players2D/players2D.c"
#include "free_roam/free_roam.c"
#include "util/player_ui.c"
#include "util/terrain_util.c"
#include "util/pause_util.c"
#include "util/resume_util.c"
#include "util/editor_util.c"
#include "util/touch_util.c"
#include "util/start_game.c"
#include "util/end_game.c"
#include "util/player_util.c"
#include "util/voxel_ray_util.c"
#include "systems/player_pause_system.c"
#include "systems/device_mode_response_system.c"
#include "systems/virtual_joystick_system.c"
#include "systems/editor_input_system.c"
#include "systems/qol_shortcuts_system.c"
#include "systems/player_shortcuts_system.c"
#include "systems/player_shortcuts_single_system.c"
#include "systems/player_toggle_camera_system.c"
#include "systems/player_test_system.c"
#include "systems/raycast_gizmo_system.c"

void initialize_players(ecs_world_t *world) {
    add_to_event_game_state((zox_game_event) { &players_game_state });
}

zox_begin_module(Players2)
zox_define_component_entity(PlayerPauseEvent)
if (headless) return;
zox_system(QolShortcutsSystem, EcsOnUpdate, [in] Keyboard)
zox_system(PlayerShortcutsSystem, EcsOnUpdate, [in] DeviceLinks, [in] GameLink, [none] players.Player)
zox_import_module(Players2D)
zox_import_module(Players3D)
zox_import_module(FreeRoam)
zox_system_1(DeviceModeResponseSystem, zox_pipelines_pre_render, [in] DeviceMode, [in] DeviceModeDirty, [in] GameLink) // note: must update before DeviceModeDirtySystem
zox_system_1(PlayerShortcutsMainThreadSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
zox_system_1(PlayerTestSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
zox_system_1(PlayerPauseSystem, zox_pip_mainthread, [in] DeviceLinks, [none] players.Player)
zox_system_1(VirtualJoystickSystem, zox_pip_mainthread, [in] DeviceLinks, [in] DeviceMode, [in] RaycasterResult, [in] GameLink, [none] players.Player)
zox_system_1(EditorInputSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
zox_system(PlayerToggleCameraSystem, EcsOnUpdate, [in] DeviceLinks, [in] CharacterLink, [in] GameLink, [none] players.Player)

zox_system_1(RaycastGizmoSystem, zox_pip_mainthread, [in] CameraLink, [in] VoxLink)
zox_system(VoxelActionASystem, EcsOnUpdate, [in] CameraLink, [in] VoxLink, [out] TriggerActionA)
zox_system(VoxelActionBSystem, EcsOnUpdate, [in] CameraLink, [in] VoxLink, [out] TriggerActionB)

initialize_players(world);
zox_prefab_set(prefab_game, PlayerLinks, { 0, NULL })
zox_prefab_set(prefab_player, PlayerPauseEvent, { 0 })
zoxel_end_module(Players2)

#endif

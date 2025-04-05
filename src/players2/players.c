#if !defined(zox_mod_players2) && defined(zox_mod_characters)
#define zox_mod_players2

// alot of systems here are actually controller ones, player + device + camera / character, or game states like pause system?
// todo: fix block voxes not destroying
// todo: add destruction animation
// todo: hold to destroy
// todo: link to inventory
// todo: pickup items
// todo: arm animations
// todo: hold item animation / spawn item held
zox_component_entity(PlayerPauseEvent)
#include "data/settings.c"
#include "states/player_state.c"
#include "util/pause_util.c"
#include "prefabs/prefabs.c"
#include "util/game_ui.c"
#include "players3D/players3D.c"
#include "players2D/players2D.c"
#include "free_roam/free_roam.c"
#include "util/terrain_util.c"
#include "util/resume_util.c"
#include "util/editor_util.c"
#include "util/touch_util.c"
#include "util/start_game2D.c"
#include "util/start_game3D.c"
#include "util/start_game.c"
#include "util/end_game.c"
#include "util/player_util.c"
#include "util/voxel_ray_util.c"
#include "systems/player_pause_system.c"
#include "systems/virtual_joystick_system.c"
#include "systems/editor_input_system.c"
#include "systems/qol_shortcuts_system.c"
#include "systems/player_shortcuts_system.c"
#include "systems/player_shortcuts_single_system.c"
#include "systems/player_toggle_camera_system.c"
#include "systems/player_test_system.c"
#include "systems/raycast_gizmo_system.c"
#include "systems/voxel_action_system.c"
#include "systems/player_place_voxel_system.c"
#include "util/camera.c"
#include "util/ui.c"

void initialize_players(ecs_world_t *world) {
    add_to_event_game_state((zox_game_event) { &players_game_state });
}

zox_begin_module(Players2)
    zox_define_component_entity(PlayerPauseEvent)
    if (headless) return;
    zox_system(QolShortcutsSystem, EcsOnUpdate, [in] DeviceLinks, [none] players.Player)
    zox_system(PlayerShortcutsSystem, EcsOnUpdate, [in] DeviceLinks, [in] GameLink, [none] players.Player)
    zox_import_module(Players2D)
    zox_import_module(Players3D)
    zox_import_module(FreeRoam)
    // zox_pipelines_pre_render
    zox_system_1(PlayerShortcutsMainThreadSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
    zox_system_1(PlayerTestSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
    zox_system_1(PlayerPauseSystem, zox_pip_mainthread, [in] DeviceLinks, [none] players.Player)
    zox_system_1(VirtualJoystickSystem, zox_pip_mainthread, [in] DeviceLink, [in] RaycasterResult, [in] ZevicePointer, [in] VirtualZeviceLink,  [none] inputs.Zevice)
    zox_system_1(EditorInputSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
    zox_system(PlayerToggleCameraSystem, EcsOnUpdate, [in] DeviceLinks, [in] CharacterLink, [in] GameLink, [none] players.Player)
    zox_system(VoxelActionASystem, EcsOnLoad, [in] RaycastVoxelData, [out] TriggerActionA)
    zox_system_1(PlayerPlaceVoxelSystem, EcsOnLoad, [in] RaycastVoxelData, [out] ActionLinks, [out] TriggerActionB)
    zox_system_1(RaycastGizmoSystem, zox_pip_mainthread, [in] CameraLink, [in] VoxLink, [out] RaycastVoxelData)
    // zox_system(RaycastGizmoSystem, EcsOnUpdate, [in] CameraLink, [in] VoxLink, [out] RaycastVoxelData)
    initialize_players(world);
    spawn_prefabs_players2(world);
zox_end_module(Players2)

#endif

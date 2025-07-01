#include "player_pause_system.c"
#include "virtual_joystick_system.c"
#include "editor_input_system.c"
#include "qol_shortcuts_system.c"
#include "player_shortcuts_system.c"
#include "player_toggle_camera_system.c"
#include "player_test_system.c"
#include "raycast_gizmo_system.c"
#include "voxel_action_system.c"
#include "action_activate_system.c"
#include "actions_shortcut_system.c"

void define_systems_players2(ecs_world_t *world) {
    zox_system(QolShortcutsSystem, EcsOnUpdate, [in] DeviceLinks, [none] players.Player)
    zox_system(PlayerShortcutsSystem, EcsOnUpdate, [in] DeviceLinks, [in] GameLink, [none] players.Player)

    // zox_pipelines_pre_render
    // zox_system_1(PlayerShortcutsMainThreadSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
    zox_system_1(PlayerTestSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
    zox_system_1(PlayerPauseSystem, zox_pip_mainthread, [in] DeviceLinks, [none] players.Player)
    zox_system_1(VirtualJoystickSystem, zox_pip_mainthread, [in] DeviceLink, [in] RaycasterResult, [in] ZevicePointer, [in] VirtualZeviceLink,  [none] inputs.Zevice)
    zox_system_1(EditorInputSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] players.Player)
    zox_system(PlayerToggleCameraSystem, EcsOnUpdate, [in] DeviceLinks, [in] CharacterLink, [in] GameLink, [none] players.Player)
#ifdef zox_mod_actions
    zox_system(ActionsShortcutSystem, EcsOnUpdate, [in] DeviceLinks, [none] players.Player)
    zox_system(VoxelActionASystem, EcsOnLoad, [in] RaycastVoxelData, [out] TriggerActionA)
    zox_system_1(ActionActivateSystem, EcsOnLoad, [in] RaycastVoxelData, [out] ActionLinks, [out] TriggerActionB)
#endif
    zox_system_1(RaycastGizmoSystem, zox_pip_mainthread, [in] CameraLink, [in] VoxLink, [out] RaycastVoxelData)
    // zox_system(RaycastGizmoSystem, EcsOnUpdate, [in] CameraLink, [in] VoxLink, [out] RaycastVoxelData)
}
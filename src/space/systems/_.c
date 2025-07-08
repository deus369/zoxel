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
    zox_system(QolShortcutsSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [none] players.Player)
    zox_system(PlayerShortcutsSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [in] games.GameLink, [none] players.Player)
    // zox_pipelines_pre_render
    // zox_system_1(PlayerShortcutsMainThreadSystem, zox_pip_mainthread, [in] inputs.DeviceLinks, [in] elements.core.CanvasLink, [none] players.Player)
    zox_system_1(PlayerTestSystem, zox_pip_mainthread, [in] inputs.DeviceLinks, [in] elements.core.CanvasLink, [none] players.Player)
    zox_system_1(PlayerPauseSystem, zox_pip_mainthread, [in] inputs.DeviceLinks, [none] players.Player)
    zox_system_1(VirtualJoystickSystem, zox_pip_mainthread, [in] inputs.DeviceLink, [in] raycasts.RaycasterResult, [in] inputs.ZevicePointer, [in] inputs.VirtualZeviceLink, [none] inputs.Zevice)
    zox_system_1(EditorInputSystem, zox_pip_mainthread, [in] inputs.DeviceLinks, [in] elements.core.CanvasLink, [none] players.Player)
    zox_system(PlayerToggleCameraSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [in] characters.CharacterLink, [in] games.GameLink, [none] players.Player)
#ifdef zox_mod_actions
    zox_system(ActionsShortcutSystem, EcsOnUpdate, [in] inputs.DeviceLinks, [none] players.Player)
    zox_system(VoxelActionASystem, EcsOnLoad, [in] chunks.RaycastVoxelData, [out] characters.TriggerActionA)
    zox_system_1(ActionActivateSystem, EcsOnLoad, [in] chunks.RaycastVoxelData, [out] actions.ActionLinks, [out] characters.TriggerActionB)
#endif
    zox_system_1(RaycastGizmoSystem, zox_pip_mainthread, [in] cameras.CameraLink, [in] voxels.VoxLink, [out] chunks.RaycastVoxelData)
    // zox_system(RaycastGizmoSystem, EcsOnUpdate, [in] cameras.CameraLink, [in] voxels.VoxLink, [out] chunks.RaycastVoxelData)
}
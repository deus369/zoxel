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
    zox_system(QolShortcutsSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [none] players.Player)
    zox_system(PlayerShortcutsSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [in] games.GameLink,
            [none] players.Player)
    // zox_pipelines_pre_render
    zox_system_1(PlayerPauseSystem, EcsPreStore,
            [in] inputs.DeviceLinks,
            [none] players.Player)
    zox_system_1(VirtualJoystickSystem, EcsPreStore,
            [in] inputs.DeviceLink,
            [in] raycasts.RaycasterResult,
            [in] inputs.ZevicePointer,
            [in] inputs.VirtualZeviceLink,
            [none] inputs.Zevice)
    zox_system_1(EditorInputSystem, EcsPreStore,
            [in] inputs.DeviceLinks,
            [in] elements.core.CanvasLink, [none] players.Player)
    zox_system_1(PlayerToggleCameraSystem, EcsOnUpdate,
            [in] players.PlayerState,
            [in] inputs.DeviceLinks,
            [in] games.GameLink,
            [in] characters.CharacterLink,
            [none] players.Player)
#ifdef zox_mod_actions
    // note: this spawns sounds
    zox_system_1(ActionsShortcutSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [none] players.Player)
    zox_system_1(VoxelActionASystem, EcsOnLoad,
            [in] chunks3.RaycastVoxelData,
            [out] characters.TriggerActionA)
    zox_system_1(ActionActivateSystem, EcsOnLoad,
            [in] chunks3.RaycastVoxelData,
            [out] actions.ActionLinks,
            [out] characters.TriggerActionB)
#endif
    zox_system_1(PlayerTestSystem, EcsPreStore,
            [in] inputs.DeviceLinks,
            [in] elements.core.CanvasLink,
            [none] players.Player)
    zox_system_1(RaycastGizmoSystem, EcsPreStore,
            [in] cameras.CameraLink,
            [in] chunks3.VoxLink,
            [out] chunks3.RaycastVoxelData)
}
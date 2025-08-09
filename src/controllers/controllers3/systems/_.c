// controller
#include "movement.c"
#include "rotation.c"
#include "jump.c"
#include "player3D_trigger_system.c"
#include "respawn.c"
#include "flying.c"
// TODO: shortcuts - move to hotkeys or something
#include "player_pause_system.c"
#include "player_toggle_camera_system.c"
#include "qol_shortcuts_system.c"
#include "editor_input_system.c"
#include "actions_shortcut_system.c"

void define_systems_controllers3D(ecs_world_t *world) {

    zox_system(Player3DMoveSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [in] inputs.DeviceMode,
            [in] characters.CharacterLink,
            [none] players.Player);
    zox_system(PlayerFlySystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [in] inputs.DeviceMode,
            [in] characters.CharacterLink,
            [none] players.Player);

    zox_system(Player3RotateSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [in] inputs.DeviceMode,
            [in] characters.CharacterLink,
            [in] cameras.CameraLink,
            [none] players.Player);
    zox_system(Player3DJumpSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [in] inputs.DeviceMode,
            [in] characters.CharacterLink,
            [none] players.Player);
    zox_system(Player3DTriggerSystem, EcsPostUpdate,
            [in] inputs.DeviceLinks,
            [in] inputs.DeviceMode,
            [in] characters.CharacterLink,
            [none] players.Player);
    zox_system_1(Player3RespawnSystem, EcsOnUpdate,
            [out] players.PlayerState,
            [out] players.PlayerRespawn,
            [out] characters.CharacterLink);
    zox_system_1(PlayerPauseSystem, EcsOnUpdate,
             [in] inputs.DeviceLinks,
             [none] players.Player);
    zox_system_1(PlayerToggleCameraSystem, EcsOnUpdate,
            [in] players.PlayerState,
            [in] inputs.DeviceLinks,
            [in] games.GameLink,
            [in] characters.CharacterLink,
            [in] cameras.CameraLink,
            [none] players.Player);

    // more shortcuts
    zox_system(QolShortcutsSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [none] players.Player)
    zox_system_1(EditorInputSystem, EcsPreStore,
            [in] inputs.DeviceLinks,
            [in] elements.core.CanvasLink,
            [none] players.Player)
    zox_system_1(ActionsShortcutSystem, EcsOnUpdate,
            [in] inputs.DeviceLinks,
            [none] players.Player);
}
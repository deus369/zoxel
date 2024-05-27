#if !defined(zox_mod_players) && defined(zox_mod_characters)
#define zox_mod_players

// alot of systems here are actually controller ones, player + device + camera / character, or game states like pause system?
#include "settings/settings.c"
zox_declare_tag(Player)
zox_declare_tag(PlayerCharacter)
zox_component_byte(PlayerState)
zox_component_entity(PlayerLink)
zox_memory_component(PlayerLinks, ecs_entity_t)
#include "states/player_state.c"
#include "prefabs/player.c"
#include "util/crosshair.c"
#include "players3D/players3D.c"
#include "players2D/players2D.c"
#include "free_roam/free_roam.c"
#include "util/player_ui.c"
#include "util/terrain_util.c"
#include "util/pause_util.c"
#include "util/editor_util.c"
#include "util/touch_util.c"
#include "util/start_game.c"
#include "util/end_game.c"
#include "util/player_util.c"
#include "systems/player_pause_system.c"
#include "systems/device_mode_response_system.c"
#include "systems/virtual_joystick_system.c"
#include "systems/editor_input_system.c"
#include "systems/qol_shortcuts_system.c"
#include "systems/player_shortcuts_system.c"
#include "systems/player_shortcuts_single_system.c"
#include "systems/player_toggle_camera_system.c"
#include "systems/player_test_system.c"

void initialize_players(ecs_world_t *world) {
    add_to_event_game_state((zox_game_event) { &players_game_state });
}

void spawn_prefabs_players(ecs_world_t *world) {
    spawn_prefab_player(world);
    spawn_prefabs_players2D(world);
    spawn_prefabs_players3D(world);
}

zox_begin_module(Players)
if (headless) return;
zox_define_tag(Player)
zox_define_tag(PlayerCharacter)
zox_define_component_byte(PlayerState)
zox_define_component_entity(PlayerLink)
zox_define_memory_component(PlayerLinks)
zox_system(QolShortcutsSystem, EcsOnUpdate, [in] Keyboard)
zox_system(PlayerShortcutsSystem, EcsOnUpdate, [in] DeviceLinks, [in] GameLink, [none] Player)
zox_import_module(Players2D)
zox_import_module(Players3D)
zox_import_module(FreeRoam)
zox_system_1(DeviceModeResponseSystem, zox_pipelines_pre_render, [in] DeviceMode, [in] DeviceModeDirty, [in] GameLink) // note: must update before DeviceModeDirtySystem
zox_system_1(PlayerShortcutsMainThreadSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] Player)
zox_system_1(PlayerTestSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] Player)
zox_system_1(PlayerPauseSystem, zox_pip_mainthread, [in] DeviceLinks, [none] Player)
zox_system_1(VirtualJoystickSystem, zox_pip_mainthread, [in] DeviceLinks, [in] DeviceMode, [in] RaycasterResult, [in] GameLink, [none] Player)
zox_system_1(EditorInputSystem, zox_pip_mainthread, [in] DeviceLinks, [in] CanvasLink, [none] Player)
zox_system(PlayerToggleCameraSystem, EcsOnUpdate, [in] DeviceLinks, [in] CharacterLink, [in] GameLink, [none] Player)
initialize_players(world);
spawn_prefabs_players(world);
zox_prefab_set(prefab_game, PlayerLinks, { 0, NULL })
zoxel_end_module(Players)

#endif

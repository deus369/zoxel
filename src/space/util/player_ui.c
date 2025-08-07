// called from game state changes
void spawn_in_game_ui(
    ecs *world,
    const entity player
) {
    if (!zox_has(player, DeviceMode) || !zox_has(player, CanvasLink)) {
        zox_log("! invalid player in [spawn_in_game_ui]\n")
        return;
    }
    const byte device_mode = zox_get_value(player, DeviceMode)
    const entity canvas = zox_get_value(player, CanvasLink)
    byte is_touch = device_mode == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    zox_geter(player, CharacterLink, characterLink)
    spawn_menu_game(world, prefab_menu_game, player, characterLink->value);
    if (is_touch) {
        spawn_in_game_ui_touch(world, player, canvas);
    }
}

void spawn_player_game_ui(
    ecs *world,
    const entity player
) {
    spawn_in_game_ui(world, player);
#ifdef zoxm_actions_ui
    const entity canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuActions, menu_actions)
    if (!menu_actions) {
        spawn_player_menu_actions(world, player);
    }
#endif
}
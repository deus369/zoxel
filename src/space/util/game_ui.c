// called from game state changes
void spawn_in_game_ui(ecs_world_t *world, const ecs_entity_t player) {
#ifdef zox_disable_player_ui
    return;
#endif
    if (!zox_has(player, DeviceMode) || !zox_has(player, CanvasLink)) {
        zox_log("! invalid player in [spawn_in_game_ui]\n")
        return;
    }
    const byte device_mode = zox_get_value(player, DeviceMode)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    byte is_touch = device_mode == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    spawn_menu_game(world, prefab_menu_game, player); // , character_group, canvas);
    if (is_touch) {
        spawn_in_game_ui_touch(world, canvas);
    }
}

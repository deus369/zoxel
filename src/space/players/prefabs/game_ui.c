ecs_entity_t game_ui_touch = 0;

void dispose_in_game_ui_touch(ecs_world_t *world) {
    zox_delete_and_set(game_ui_touch)
}

void dispose_in_game_ui(ecs_world_t *world, ecs_entity_t player) {
    dispose_in_game_ui_touch(world);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuGame, game_ui)
    if (game_ui) zox_delete(game_ui)
}

void toggle_pause_ui(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const unsigned char game_state = zox_get_value(game, GameState)
    if (!(game_state == zox_game_playing || game_state == zox_game_paused)) return;
    unsigned char is_paused = game_state == zox_game_paused;
    if (!is_paused) set_game_state_target(world, game, zox_game_paused);
    else set_game_state_target(world, game, zox_game_playing);
}

// from touch_ui
void button_event_pause_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    toggle_pause_ui(world, player);
}

void spawn_in_game_ui_touch(ecs_world_t *world, const ecs_entity_t canvas) {
    if (game_ui_touch) return;
    const unsigned char pause_button_size = 80;
    const ClickEvent on_pause_ui = (ClickEvent) { &button_event_pause_game };
    game_ui_touch = spawn_button_on_canvas(world, canvas, (int2) { pause_button_size, pause_button_size }, (byte2) { 8, 4 }, (color) { 77, 32, 44, 255 }, "P", pause_button_size, float2_zero, on_pause_ui);
    // zox_log("  > spawning touch ui [%lu]\n", game_ui_touch)
}

void spawn_in_game_ui(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_2 character_group) {
#ifdef zox_disable_player_ui
    return;
#endif
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (is_touch) spawn_in_game_ui_touch(world, canvas);
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t e = spawn_element_invisible_on_canvas(world, canvas, int2_zero, canvas_size, float2_half);
    zox_name("game_ui")
    zox_add_tag(e, MenuGame)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_add(e, Children)
    Children *game_ui_children = zox_get_mut(e, Children)
    add_to_Children(game_ui_children, spawn_crosshair(world, canvas, e));
#ifndef zox_disable_statbars
    add_to_Children(game_ui_children, spawn_statbar2D(world, canvas, e, player, character_group));
#endif
    zox_modified(e, Children)
}

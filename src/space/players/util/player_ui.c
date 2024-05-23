ecs_entity_t game_ui_touch = 0;

void dispose_in_game_ui_touch(ecs_world_t *world) {
    zox_delete_and_set(game_ui_touch)
}

void dispose_in_game_ui(ecs_world_t *world, ecs_entity_t player) {
    dispose_in_game_ui_touch(world);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuInGame, game_ui)
    zox_delete(game_ui)
}

void toggle_pause_ui(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const GameState *gameState = zox_get(game, GameState)
    if (!(gameState->value == zox_game_playing || gameState->value == zox_game_paused)) return;
    unsigned char is_paused = gameState->value == zox_game_paused;
    if (!is_paused) trigger_event_game(world, game, zox_game_paused);
    else trigger_event_game(world, game, zox_game_playing);
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
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (is_touch) spawn_in_game_ui_touch(world, canvas);
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t game_ui = spawn_element_invisible_on_canvas(world, canvas, int2_zero, canvas_size, float2_half);
    zox_add_tag(game_ui, MenuInGame)
    zox_prefab_set(game_ui, AnchorSize, { float2_one })
    zox_prefab_set(game_ui, Children, { 0, NULL })
    on_child_added(world, canvas, game_ui);
    Children *game_ui_children = zox_get_mut(game_ui, Children)
    add_to_Children(game_ui_children, spawn_crosshair(world, canvas, game_ui));
    add_to_Children(game_ui_children, spawn_actionbar(world, canvas, game_ui));
    add_to_Children(game_ui_children, spawn_healthbar_on_canvas(world, canvas, game_ui, player, character_group));
    zox_modified(game_ui, Children)
}

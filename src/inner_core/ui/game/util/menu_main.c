extern ecs_entity_t spawn_menu_options(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor);

void button_event_play_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) return;
    zox_delete(menu)
    const ecs_entity_t game = zox_get_value(player, GameLink)
    trigger_event_game(world, game, zox_game_playing);
}

void button_event_menu_options(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) return;
    zox_delete(menu)
    spawn_menu_options(world, player, canvas, int2_zero, float2_half);
}

void engine_end_delayed(ecs_world_t* world, const ecs_entity_t null) {
    engine_end();
}

void button_event_exit_app(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    // zox_log(" player exiting [%s]\n", zox_get_name(player))
    // close on all players
    const ecs_entity_t game = zox_get_value(player, GameLink)
    const PlayerLinks *players = zox_get(game, PlayerLinks)
    for (int i = 0; i < players->length; i++) {
        const ecs_entity_t e = players->value[i];
        const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
        find_child_with_tag(canvas, MenuMain, menu)
        if (menu) zox_delete(menu)
        trigger_canvas_fade_in(world, canvas);
    }
    delay_event(world, &engine_end_delayed, 0, 2.0f);
}

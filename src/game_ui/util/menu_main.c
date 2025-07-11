extern ecs_entity_t spawn_menu_options(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor);

void button_event_menu_options(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t canvas = zox_get_value(event->clicker, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (!menu) {
        return;
    }
    zox_delete(menu)
    spawn_menu_options(world, event->clicker, canvas, int2_zero, float2_half);
}

void engine_end_delayed(ecs_world_t* world, const ecs_entity_t null) {
    engine_end();
}

void button_event_exit_app(ecs_world_t *world, const ClickEventData *event) {
    disable_time_pausing();
    // close on all players
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    zox_geter(game, PlayerLinks, players)
    for (int i = 0; i < players->length; i++) {
        const ecs_entity_t e = players->value[i];
        const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
        find_child_with_tag(canvas, MenuMain, menu)
        if (menu) {
            zox_delete(menu)
        }
        trigger_canvas_fade_in(world, canvas);
    }
    delay_event(world, &engine_end_delayed, 0, 2.0f);
}
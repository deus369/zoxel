void button_event_end_game(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t game = zox_get_value(event->clicker, GameLink)
    zox_geter(game, PlayerLinks, players)
    for (int i = 0; i < players->length; i++) {
        const ecs_entity_t e = players->value[i];
        const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
        find_child_with_tag(canvas, MenuPaused, menu_paused)
        if (menu_paused) zox_delete(menu_paused)
        find_child_with_tag(canvas, Taskbar, taskbar)
        if (taskbar) zox_delete(taskbar)
    }
    zox_set(game, GameStateTarget, { zox_game_start })
}

void button_event_return_to_game(ecs_world_t *world, const ClickEventData *event) {
    pause_resume(world, event->clicker);
}
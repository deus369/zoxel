void engine_end_delayed(ecs_world_t* world, const ecs_entity_t null) {
    engine_end();
}

void button_event_exit_app(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuMain, menu)
    if (menu) zox_delete(menu)
    trigger_canvas_fade_transition(world, canvas);
    delay_event(world, &engine_end_delayed, 0, 2.0f);
}

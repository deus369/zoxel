ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_menu_paused")
    zox_add_tag(e, MenuPaused)
    prefab_menu_paused = e;
    return e;
}

// extern void pause_resume(ecs_world_t *world, const ecs_entity_t player);

void button_event_return_to_game(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    pause_resume(world, player);
}

ecs_entity_t spawn_menu_paused(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor) {
    const int labels_count = 2;
    const text_group labels[] = { { "return" }, { "leave" } };
    const ClickEvent events[] = { { &button_event_return_to_game }, { &button_event_end_game } };
    const unsigned char layer = 1;
    const ecs_entity_t e = spawn_ui_list(world, prefab_menu_paused, canvas, "paused", labels_count, labels_count, labels, events, position, anchor, 0, 28, layer, 0, player);
    zox_name("menu_paused")
    return e;
}

ecs_entity_t pause_ui_prefab;
ecs_entity_t pause_ui;

ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(window_prefab)
    zox_name("prefab_pause_ui")
    zox_add_tag(e, PauseUI);
    ecs_defer_end(world);
    pause_ui_prefab = e;
    return e;
}

ecs_entity_t spawn_pause_ui(ecs_world_t *world, int2 position, float2 anchor) {
    int labels_count = 2;
    const text_group labels[] = { { "return" }, { "leave" } };
    ClickEvent events[] = { { &button_event_return_to_game }, { &button_event_stop_playing_game } };
    ecs_entity_t e = spawn_ui_list(world, prefab_main_menu, "paused", labels_count, labels, events, position, anchor, 0);
    pause_ui = e;
    return e;
}
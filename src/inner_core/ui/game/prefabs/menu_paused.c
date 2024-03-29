ecs_entity_t prefab_menu_paused;
ecs_entity_t pause_ui;

ecs_entity_t spawn_prefab_pause_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_menu_paused")
    zox_add_tag(e, MenuPaused)
    prefab_menu_paused = e;
    return e;
}

ecs_entity_t spawn_pause_ui(ecs_world_t *world, int2 position, float2 anchor) {
    const int labels_count = 2;
    const text_group labels[] = { { "return" }, { "leave" } };
    const ClickEvent events[] = { { &button_event_return_to_game }, { &button_event_end_game } };
    const unsigned char layer = 1;
    ecs_entity_t e = spawn_ui_list(world, prefab_menu_paused, main_canvas, "paused", labels_count, labels_count, labels, events, position, anchor, 0, 28, layer, 0);
    pause_ui = e;
    zox_name("menu_paused")
    // zoxel_log(" > spawn_pause_ui alive ui? %s\n", ecs_is_alive(world, pause_ui) ? "alive" : "dead");
    return e;
}

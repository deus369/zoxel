// this will handle resume game & exit game & options
ecs_entity_t spawn_prefab_options_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_menu_options")
    zox_add_tag(e, MenuOptions);
    return e;
}

ecs_entity_t spawn_menu_options(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const int2 position, const float2 anchor) {
    const byte is_close_button = 0;
    const int labels_count = 3;
    const text_group labels[] = { { "volume +" }, { "volume -" }, { "return" } };
    const ClickEvent events[] = { { &button_event_volume_increase }, { &button_event_volume_decrease }, { &button_event_menu_main } };
    const byte layer = 1;
    const ecs_entity_t e = spawn_ui_list(world, prefab_menu_options, canvas, "options", labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0, player);
    zox_name("menu_options")
    return e;
}

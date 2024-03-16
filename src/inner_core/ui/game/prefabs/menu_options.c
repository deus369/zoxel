// this will handle resume game & exit game & options
ecs_entity_t prefab_menu_options;
ecs_entity_t menu_options;

ecs_entity_t spawn_prefab_options_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_menu_options")
    zox_add_tag(e, MenuOptions);
    prefab_menu_options = e;
    return e;
}

ecs_entity_t spawn_menu_options(ecs_world_t *world, int2 position, float2 anchor) {
    float2 main_menu_anchor = { 0.5f, 0.5f };
    int2 main_menu_position = int2_zero;
    const unsigned char is_close_button = 0;
    int labels_count = 3;
    const text_group labels[] = { { "volume +" }, { "volume -" }, { "return" } };
    const ClickEvent events[] = { { &button_event_volume_increase }, { &button_event_volume_decrease }, { &button_event_menu_main } };
    const unsigned char layer = 1;
    ecs_entity_t e = spawn_ui_list(world, prefab_menu_options, main_canvas, "options", labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0);
    zox_name("menu_options")
    menu_options = e;
    return e;
}

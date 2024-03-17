ecs_entity_t prefab_main_menu;
ecs_entity_t main_menu;

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_main_menu")
    zox_add_tag(e, MenuMain)
    prefab_main_menu = e;
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, float2 anchor) {
    const unsigned char is_close_button = 0;
#ifdef zoxel_on_android
    int labels_count = 1;
    const text_group labels[] = { { "enter" }, { "options" } };
    const ClickEvent events[] = { { &button_event_play_game }, { &button_event_menu_options } };
#else
    int labels_count = 3;
    const text_group labels[] = { { "enter" }, { "options" }, { "exit" } };
    const ClickEvent events[] = { { &button_event_play_game }, { &button_event_menu_options }, { &button_event_exit_app } };
#endif
    const unsigned char layer = 1;
    ecs_entity_t e = spawn_ui_list(world, prefab_main_menu, main_canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0);
    zox_name("main_menu")
    main_menu = e;
    return e;
}

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_main_menu")
    zox_add_tag(e, MenuMain)
    prefab_main_menu = e;
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const char *header_label, const int2 position, const float2 anchor) {
    const unsigned char is_close_button = 0;
    const unsigned char layer = 3;
    // enter
    ecs_entity_t e = 0;
    int labels_count = 0;
#ifdef zoxel_on_android
    labels_count = 2;
    const text_group labels[] = { { "new game" }, { "options" } };
    const ClickEvent events[] = { { &button_event_new_game }, { &button_event_menu_options } };
    e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0, player);
#else
    if (!has_save_game_directory("zoxel")) {
        labels_count = 3;
        const text_group labels[] = { { "new game" }, { "options" }, { "exit" } };
        const ClickEvent events[] = { { &button_event_new_game }, { &button_event_menu_options }, { &button_event_exit_app } };
        e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0, player);
    } else {
        labels_count = 4;
        const text_group labels[] = { { "continue" }, { "new game" }, { "options" }, { "exit" } };
        const ClickEvent events[] = { { &button_event_continue_game }, { &button_event_new_game }, { &button_event_menu_options }, { &button_event_exit_app } };
        e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, 42, layer, 0, player);
    }
#endif
    zox_name("main_menu")
    return e;
}

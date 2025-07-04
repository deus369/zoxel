char *label_continue = "continue"; // "old blood";
char *label_new = "new game"; // "fresh meat";
char *label_options = "options";
char *label_exit = "exit";

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_list)
    zox_prefab_name("prefab_main_menu")
    zox_add_tag(e, MenuMain)
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t canvas, const char *header_label, const int2 position, const float2 anchor) {
    const byte font_size = 64;
    const byte header_font_size = 96;
    const byte is_close_button = 0;
    const byte layer = 3;
    // enter
    ecs_entity_t e = 0;
    int labels_count = 0;
#ifdef zoxel_on_android
    if (!has_save_game_directory(game_name)) {
        labels_count = 2;
        const text_group labels[] = { { label_new }, { label_options }};
        const ClickEvent events[] = { { &button_event_new_game }, { &button_event_menu_options } };
        e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, header_font_size, font_size, layer, 0, player);
    } else {
        labels_count = 3;
        const text_group labels[] = { { label_continue }, { label_new }, { label_options } };
        const ClickEvent events[] = { { &button_event_continue_game }, { &button_event_new_game }, { &button_event_menu_options } };
        e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, header_font_size, font_size, layer, 0, player);
    }
#else
    if (!has_save_game_directory(game_name)) {
        labels_count = 3;
        const text_group labels[] = { { label_new }, { label_options }, { label_exit } };
        const ClickEvent events[] = { { &button_event_new_game }, { &button_event_menu_options }, { &button_event_exit_app } };
        e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, header_font_size, font_size, layer, 0, player);
    } else {
        labels_count = 4;
        const text_group labels[] = { { label_continue }, { label_new }, { label_options }, { label_exit } };
        const ClickEvent events[] = { { &button_event_continue_game }, { &button_event_new_game }, { &button_event_menu_options }, { &button_event_exit_app } };
        e = spawn_ui_list(world, prefab_main_menu, canvas, header_label, labels_count, labels_count, labels, events, position, anchor, is_close_button, header_font_size, font_size, layer, 0, player);
    }
#endif
    zox_name("main_menu")
    return e;
}
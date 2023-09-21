ecs_entity_t prefab_main_menu;
ecs_entity_t main_menu;

ecs_entity_t spawn_prefab_main_menu(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_ui_list)    // prefab_window
    zox_name("prefab_main_menu")
    zox_add_tag(e, MainMenu)
    ecs_defer_end(world);
    prefab_main_menu = e;
    return e;
}

ecs_entity_t spawn_main_menu(ecs_world_t *world, const char *header_label, int2 position, float2 anchor, unsigned char is_close_button) {
#ifdef zoxel_on_android
    int labels_count = 1;
    const text_group labels[] = { { "play" } };
    const ClickEvent events[] = { { &button_event_play_game } };
#else
    int labels_count = 2;
    const text_group labels[] = { { "play" }, { "exit" } };
    const ClickEvent events[] = { { &button_event_play_game }, { &button_event_exit_app } };
#endif
    ecs_entity_t e = spawn_ui_list(world, prefab_main_menu, "zoxel", labels_count, labels, events,
        position, anchor, is_close_button, 42);
    main_menu = e;
    return e;
}

// options
/*int labels_count = 3;
const text_group labels[] = { { "play" }, { "options" }, { "exit" } };
ClickEvent events[] = { { &button_event_play_game }, { NULL }, { &button_event_exit_app } };*/
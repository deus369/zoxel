ecs_entity_t spawn_main_menu(ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const char *header_label,
    const int2 position,
    const float2 anchor)
{
    const byte font_size = 64;
    const byte header_font_size = 96;
    const byte is_close_button = 0;
    const byte layer = 3;
    const int max_labels = 5;
    text_group labels[max_labels];
    ClickEvent events[max_labels];
    int labels_count = 0;
    if (has_save_game_directory(game_name)) {
        labels[labels_count] = (text_group) { label_continue };
        events[labels_count] = (ClickEvent) { button_event_continue_game };
        labels_count++;
    }
    labels[labels_count] = (text_group) { label_new };
    events[labels_count] = (ClickEvent) { button_event_new_game };
    labels_count++;
    labels[labels_count] = (text_group) { label_options };
    events[labels_count] = (ClickEvent) { button_event_menu_options };
    labels_count++;
#ifndef zoxel_on_android
    labels[labels_count] = (text_group) { label_exit };
    events[labels_count] = (ClickEvent) { button_event_exit_app };
    labels_count++;
#endif
    ecs_entity_t e = spawn_ui_list(world,
        prefab_ui_list,
        canvas,
        header_label,
        labels_count,
        labels_count,
        labels,
        events,
        NULL,
        NULL,
        position,
        anchor,
        is_close_button,
        header_font_size,
        font_size,
        layer,
        0,
        player);
    zox_name("main_menu")
    zox_add_tag(e, MenuMain)
    return e;
}
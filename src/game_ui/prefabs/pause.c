ecs_entity_t spawn_menu_paused(ecs_world_t *world,
    const ecs_entity_t player)
{
    // getters
    zox_geter_value(player, CanvasLink, ecs_entity_t, canvas)
    // settings
    const byte font_size = 48;
    const byte header_font_size = 60;
    const float2 anchor = (float2) { 0.0f, 1.0f };
    const int2 position = (int2) { 200, -200 };
    const byte layer = pause_ui_overlay_layer + 3;
    const byte is_close_button = 0;
    const int max_labels = 5;
    text_group labels[max_labels];
    ClickEvent events[max_labels];
    int labels_count = 0;
    labels[labels_count] = (text_group) { pause_label_confirm };
    events[labels_count] = (ClickEvent) { button_event_return_to_game };
    labels_count++;
    labels[labels_count] = (text_group) { pause_label_exit };
    events[labels_count] = (ClickEvent) { button_event_end_game };
    labels_count++;

    const ecs_entity_t e = spawn_ui_list(world,
        prefab_ui_list,
        canvas,
        menu_paused_header_label,
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
    zox_add_tag(e, MenuPaused)
    zox_name("menu_paused")
    return e;
}
ecs_entity_t spawn_menu_paused(
    ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const int2 position,
    const float2 anchor,
    const byte layer)
{
    const byte header_font_size = 40;
    const byte font_size = 32;
    const byte is_close_button = 0;
    const int max_labels = 5;
    text_group labels[max_labels];
    ClickEvent events[max_labels];
    int labels_count = 0;
    labels[labels_count] = (text_group) { pause_label_confirm };
    events[labels_count] = (ClickEvent) { button_event_return_to_game };
    labels_count++;
#ifndef zox_disable_save_games
    if (has_save_game_directory(game_name)) {
        labels[labels_count] = (text_group) { pause_label_save };
        events[labels_count] = (ClickEvent) { button_event_save_game };
        labels_count++;
    }
#endif
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

ecs_entity_t spawn_player_menu_paused(ecs_world_t *world, const ecs_entity_t player) {
    // const float2 anchor = float2_half;  // (float2) { 0, 1 };
    // const int2 position = int2_zero;    // (int2) { 100, -100 };
    const float2 anchor = (float2) { 0.0f, 1.0f };
    const int2 position = (int2) { 200, -200 };
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    return spawn_menu_paused(world,
        player,
        canvas,
        position,
        anchor,
        pause_ui_overlay_layer + 3);
}
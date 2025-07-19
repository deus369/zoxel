ecs_entity_t spawn_main_menu(ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const char *header_label)
{
    const byte window_layer = 3;
    // # Window #
    // window_fill = color_grayscale(10);
    // window_outline = color_grayscale(44);
    CanvasSpawnData canvas_data = {
        .e = canvas,
        .size = zox_gett_value(canvas, PixelSize),
    };
    ElementSpawnData window_element_data = {
        .prefab = prefab_window,
        .position = (int2) { 200, -200 },
        .anchor = (float2) { 0.0f, 1.0f },
        .layer = window_layer,
    };
    ParentSpawnData window_parent_data = {
        .e = canvas_data.e,
        .size = canvas_data.size,
        .position = int2_half(canvas_data.size),
    };
    SpawnWindow2 window_data = {
        .header_text = header_label,
        .header_font_size = 80,
        .header_padding = 4,
        .is_scrollbar = 0,
    };
    int header_height = window_data.header_font_size + window_data.header_padding * 2;

    // # List #
    SpawnListElement elements[4];
    int elements_count = 0;
    if (has_save_game_directory(game_name)) {
        elements[elements_count++] = (SpawnListElement) {
            .text = label_continue,
            .on_click = &button_event_continue_game,
        };
    }
    elements[elements_count++] = (SpawnListElement) {
        .text = label_new,
        .on_click = &button_event_new_game,
    };
    elements[elements_count++] = (SpawnListElement) {
        .text = label_options,
        .on_click = &button_event_menu_options,
    };
#ifndef zoxel_on_android
    elements[elements_count++] = (SpawnListElement) {
        .text = label_exit,
        .on_click = &button_event_exit_app,
    };
#endif
    SpawnList list_data = (SpawnList) {
        .elements = elements,
        .count = elements_count,
        .visible_count = elements_count,
        .font_size = 60,
        .fill = button_fill,
        .outline = button_outline,
        .padding = 8,
        .spacing = 18,
    };

    // Our window again, spawn using list size
    // calculate size
    window_element_data.size = calculate_list_size(
        calculate_list_max_characters(list_data),
        list_data.font_size,
        list_data.padding,
        list_data.spacing,
        list_data.visible_count);
    window_element_data.size.y += header_height;
    // zox_log("+ calculated size for list [%ix%i]", window_element_data.size.x, window_element_data.size.y)
    const ecs_entity_t e = spawn_window2(world,
        canvas_data,
        window_parent_data,
        &window_element_data,
        &window_data);
    zox_name("main_menu")
    zox_add_tag(e, MenuMain)

    // finish our list
    ParentSpawnData list_parent_data = {
        .e = e,
        .size = window_element_data.size,
        .position = window_element_data.position_in_canvas,
    };
    ElementSpawnData list_element_data = {
        .prefab = prefab_list,
        .position = (int2) { 0, -header_height / 2 },
        .size = (int2) { window_element_data.size.x, window_element_data.size.y - header_height },
        .anchor = float2_half,
        .layer = window_layer + 1,
    };
    const ecs_entity_t list = spawn_list(world,
        canvas_data,
        list_parent_data,
        list_element_data,
        list_data);
    add_to_Children(window_data.children, list);


    /*text_group labels[max_labels];
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
    zox_add_tag(e, MenuMain)*/

    return e;
}
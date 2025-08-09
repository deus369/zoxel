// List Menus adjust to the menu size
ecs_entity_t spawn_main_menu(
    ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas,
    const char *header_label
) {
    const byte window_layer = 3;
    const byte header_font_size = 72;
    byte2 list_margins = (byte2) { 32, 18 };
    byte list_font_size = 44;

    // # Window #
    // window_fill = color_grayscale(10);
    // window_outline = color_grayscale(44);
    CanvasSpawnData canvas_data = {
        .e = canvas,
        .size = zox_gett_value(canvas, PixelSize),
    };
    ElementSpawnData window_element_data = {
        .prefab = prefab_window,
        .position = int2_zero, // (int2) { 200, -200 },
        .anchor = float2_half, // (float2) { 0.0f, 1.0f },
        .layer = window_layer,
    };
    ParentSpawnData window_parent_data = {
        .e = canvas_data.e,
        .size = canvas_data.size,
        .position = int2_half(canvas_data.size),
    };
    SpawnWindow2 window_data = {
        .header_text = header_label,
        .header_font_size = header_font_size,
        .header_padding = (byte2) { 24, 8 },
        .is_scrollbar = 0,
    };
    // we need to calculate header size too
    int2 header_size = calculate_header_size(
        strlen(header_label),
        window_data.header_font_size,
        window_data.header_padding);
    int header_height = header_size.y;

    // # List #
    SpawnListElement elements[4];
    int elements_count = 0;
    if (has_save_game_directory(game_name)) {
        elements[elements_count++] = (SpawnListElement) {
            .text = label_continue,
            .on_click = { &button_event_continue_game },
        };
    }
    elements[elements_count++] = (SpawnListElement) {
        .text = label_new,
        .on_click = { &button_event_new_game },
    };
    elements[elements_count++] = (SpawnListElement) {
        .text = label_options,
        .on_click = { &button_event_menu_options },
    };
#ifndef zox_android
    elements[elements_count++] = (SpawnListElement) {
        .text = label_exit,
        .on_click = { &button_event_exit_app },
    };
#endif
    SpawnList list_data = (SpawnList) {
        .elements = elements,
        .count = elements_count,
        .visible_count = elements_count,
        .font_size = list_font_size,
        .fill = button_fill,
        .outline = button_outline,
        .padding = (byte2) { 18, 8 },
        .spacing = 18,
    };

    // Our window again, spawn using list size
    // calculate size
    int2 list_size = calculate_list_size(
        calculate_list_max_characters(list_data),
        list_data.font_size,
        list_data.padding,
        list_data.spacing,
        list_margins,
        list_data.visible_count);
    // we use the bigger size out of list and header widths
    window_element_data.size = (int2) {
        int_max(list_size.x, header_size.x),
        list_size.y + header_height
    };

    Children children = (Children) { 0 };
    window_data.children = &children;
    const ecs_entity_t e = spawn_window2(
        world,
        canvas_data,
        window_parent_data,
        &window_element_data,
        &window_data);
    zox_name("main_menu");
    zox_add_tag(e, MenuMain);

    // finish our list
    ParentSpawnData list_parent_data = {
        .e = e,
        .size = window_element_data.size,
        .position = window_element_data.position_in_canvas,
    };
    ElementSpawnData list_element_data = {
        .prefab = prefab_list,
        .position = (int2) {
            0,
            -header_height / 2
        },
        .size = (int2) {
            window_element_data.size.x,
            window_element_data.size.y - header_height
        },
        .anchor = float2_half,
        .layer = window_layer + 1,
    };
    const ecs_entity_t list = spawn_list(world,
        canvas_data,
        list_parent_data,
        list_element_data,
        list_data);
    add_to_Children(window_data.children, list);

    zox_set_ptr(e, Children, children);

    zox_muter(player, ElementLinks, pelements);
    add_to_ElementLinks(pelements, e);
    zox_set(e, ElementHolder, { player });

    return e;
}
ecs_entity_t spawn_prefab_ui_list(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_ui_list")
    zox_prefab_set(e, ListUIMax, { 0 })
    return e;
}

int get_max_characters(const char *header_label, const text_group labels[], int elements_count) {
    int max_characters = 0; // get max text length out of all of the words
    for (int i = 0; i < elements_count; i++) {
        int txt_size = strlen(labels[i].text);
        if (txt_size > max_characters) max_characters = txt_size;
    }
    int header_txt_size = strlen(header_label);
    if (header_txt_size > max_characters) max_characters = header_txt_size;
    return max_characters;
}

// todo: use struct inputs
ecs_entity_t spawn_ui_list(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const char *header_label, const int elements_count, const int max_elements, const text_group labels[], const ClickEvent events[], int2 pixel_position, const float2 anchor, const unsigned char is_close_button, unsigned char font_size, const unsigned char layer, const unsigned char is_scrollbar, const ecs_entity_t player) {
    const ecs_entity_t parent = canvas;
    const unsigned char is_header = 1;
    const unsigned char list_start = is_header + is_scrollbar;
    const int children_length = (list_start + elements_count);
    const int max_characters = get_max_characters(header_label, labels, elements_count);
    const int scaled_font_size = default_ui_scale * (int) font_size;
    const int scrollbar_width = 36 * default_ui_scale;
    const int scrollbar_margins = 8 * default_ui_scale;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const unsigned char header_layer = layer + 1;
    const unsigned char button_layer = layer + 1;
    const int header_margins = scaled_font_size / 2;
    const int header_height = (scaled_font_size + header_margins - 1);
    const int2 list_margins = (int2) { (int) (scaled_font_size * 0.8f), (int) (scaled_font_size * 0.8f) };
    const byte2 button_padding = (byte2) { (int) (scaled_font_size * 0.46f), (int) (scaled_font_size * 0.3f) };
    const int button_inner_margins = (int) (scaled_font_size * 0.5f);
    int2 pixel_size = { (scaled_font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, (scaled_font_size + button_padding.y * 2) * max_elements + button_inner_margins * (max_elements - 1) + list_margins.y * 2 };
    if (is_scrollbar) pixel_size.x += (scrollbar_width / 2) + scrollbar_margins;
    anchor_element_position2D_with_header(&pixel_position, anchor, pixel_size, header_height);
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab)
    zox_name("ui_list")
    zox_set(e, ListUIMax, { max_elements })
    zox_set(e, ElementFontSize, { font_size })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    Children *children = zox_get_mut(e, Children)
    initialize_memory_component(Children, children, ecs_entity_t, children_length)
    if (is_header) {
        // scaled_font_size + header_margins
        const int2 header_size = (int2) { pixel_size.x, header_height };
        const int2 header_position = (int2) { 0, header_height / 2 };
        const float2 header_anchor = (float2) { 0.5f, 1.0f };
        children->value[0] = spawn_header(world, e, canvas, header_position, header_size, header_anchor, header_label, scaled_font_size, header_margins, header_layer, pixel_position_global, pixel_size, is_close_button, canvas_size);
        // zox_set(e, HeaderHeight, { header_size.y })
    }
    set_window_bounds_to_canvas(world, e, canvas_size, pixel_size, anchor);
    if (is_scrollbar) children->value[is_header] = spawn_scrollbar(world, e, canvas, (int2) { -(scrollbar_width / 2) - scrollbar_margins, 0 }, header_layer, pixel_position_global, pixel_size, scrollbar_width, scrollbar_margins, canvas_size, elements_count, max_elements);
    SpawnButton spawnButton = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = e,
            .position = pixel_position_global,
            .size = pixel_size
        },
        .element = {
            .prefab = prefab_button,
            .layer = button_layer,
            .anchor = float2_half
        },
        .zext = {
            .text = "X",
            .font_size = scaled_font_size,
            .font_thickness = 1,
            .padding = button_padding,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color
        },
        .button = {
            .color = button_color,
            .prefab_zext = prefab_zext
        }};
    for (int i = 0; i < elements_count; i++) {
        int2 label_position = (int2) { 0, (int) (pixel_size.y / 2) - (i + 0.5f) * (scaled_font_size + button_padding.y * 2) - list_margins.y - i * button_inner_margins };
        if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
        spawnButton.zext.text = labels[i].text;
        spawnButton.element.position = label_position;
        const ecs_entity_t button = spawn_button(world, &spawnButton);
        if (events && events[i].value) zox_set(button, ClickEvent, { events[i].value })
        children->value[list_start + i] = button;
        zox_add_tag(button, ZextLabel)
    }
    zox_modified(e, Children)
#ifdef zoxel_include_players
    if (!headless && elements_count > 0 && player) {
        const unsigned char device_mode = zox_get_value(player, DeviceMode)
        if (device_mode == zox_device_mode_gamepad) raycaster_select_element(world, player, children->value[list_start]);
    }
#endif
    return e;
}

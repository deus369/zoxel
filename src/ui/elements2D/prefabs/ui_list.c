ecs_entity_t spawn_prefab_ui_list(ecs_world_t *world, ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_ui_list")
    zox_prefab_set(e, ListUIMax, { 0 })
    return e;
}

int get_max_width(
    const char *header_label,
    int header_font_size,
    int header_padding,
    const text_group labels[],
    int elements_count,
    int element_font_size,
    int element_padding) {
    int max_characters = 0; // get max text length out of all of the words
    for (int i = 0; i < elements_count; i++) {
        int txt_size = strlen(labels[i].text);
        if (txt_size > max_characters) {
            max_characters = txt_size;
        }
    }
    int header_txt_size = strlen(header_label);
    int element_width = element_font_size * max_characters + element_padding * 2;
    int header_width = header_font_size * header_txt_size + header_padding * 2;
    if (header_width > element_width) {
        return header_width;
    } else {
        return element_width;
    }
}

// todo: use struct inputs SpawnUIList
ecs_entity_t spawn_ui_list(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t canvas,
    const char *header_label,
    const int elements_count,
    const int max_elements,
    const text_group labels[],
    const ClickEvent events[],
    int2 pixel_position,
    const float2 anchor,
    const byte is_close_button,
    byte header_font_size,
    byte font_size,
    const byte layer,
    const byte is_scrollbar,
    const ecs_entity_t player)
{
    const ecs_entity_t parent = canvas;
    const byte is_header = 1;
    const byte list_start = is_header + is_scrollbar;
    const int children_length = (list_start + elements_count);
    const int scaled_font_size = zox_ui_scale * (int) font_size;
    const int scaled_header_font_size = zox_ui_scale * (int) header_font_size;
    const int scrollbar_width = 36 * zox_ui_scale;
    const int scrollbar_margins = 8 * zox_ui_scale;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    // header
    const byte header_layer = layer + 1;
    const int header_padding_x = (int)(scaled_header_font_size * 0.6f);
    const int header_padding_y = (int)(scaled_header_font_size * 0.33f);
    const int header_height = (scaled_header_font_size + header_padding_y * 2);
    // list
    const byte button_layer = layer + 1;
    const int2 list_margins = (int2) { (int) (scaled_font_size * 0.8f), (int) (scaled_font_size * 0.8f) };
    const byte2 button_padding = (byte2) { (int) (scaled_font_size * 0.46f), (int) (scaled_font_size * 0.3f) };
    const int button_inner_margins = (int) (scaled_font_size * 0.5f);
    const int window_width = get_max_width(header_label, scaled_header_font_size, header_padding_x, labels, elements_count, scaled_font_size, button_padding.x + list_margins.x);

    int2 pixel_size = { window_width, (scaled_font_size + button_padding.y * 2) * max_elements + button_inner_margins * (max_elements - 1) + list_margins.y * 2 };

    if (is_scrollbar) {
        pixel_size.x += (scrollbar_width / 2) + scrollbar_margins;
    anchor_element_position2D_with_header(&pixel_position, anchor, pixel_size, header_height);
    }
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab)
    zox_name("ui_list")
    zox_set(e, ListUIMax, { max_elements })
    zox_set(e, ElementFontSize, { scaled_font_size })
    initialize_element(world,
        e,
        parent,
        canvas,
        pixel_position,
        pixel_size,
        pixel_size,
        anchor,
        layer,
        position2D,
        pixel_position_global);
    Children *children = &((Children) { 0, NULL });
    initialize_memory_component(Children, children, ecs_entity_t, children_length)
    if (is_header) {
        const int2 header_size = (int2) { pixel_size.x, header_height };
        const int2 header_position = (int2) { 0, header_height / 2 };
        const float2 header_anchor = (float2) { 0.5f, 1.0f };
        children->value[0] = spawn_header(world,
            e,
            canvas,
            header_position,
            header_size,
            header_anchor,
            header_label,
            scaled_header_font_size,
            header_padding_x,
            header_layer,
            pixel_position_global,
            pixel_size,
            is_close_button,
            canvas_size);
    }
    set_window_bounds_to_canvas(world, e, canvas_size, pixel_size, anchor);
    if (is_scrollbar) {
        const ecs_entity_t scrollbar = spawn_scrollbar(
            world,
            e,
            canvas,
            (int2) { -(scrollbar_width / 2) - scrollbar_margins, 0 }, header_layer,
            pixel_position_global,
            pixel_size,
            scrollbar_width,
            scrollbar_margins,
            canvas_size,
            elements_count,
            max_elements);
        children->value[is_header] = scrollbar;
    }
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
        .button = {
            .prefab_zext = prefab_zext,
            .fill = button_fill,
            .outline = button_outline,
        },
        .zext = {
            // .text = "X",
            .font_size = scaled_font_size,
            .padding = button_padding,
            .font_resolution = button_font_resolution,
            .font_fill_color = button_font_fill,
            .font_outline_color = button_font_outline,
            .font_thickness = button_font_thickness_fill,
            .font_outline_thickness = button_font_thickness_outline,

        },
    };
    for (int i = 0; i < elements_count; i++) {
        int2 label_position = (int2) { 0, (int) (pixel_size.y / 2) - (i + 0.5f) * (scaled_font_size + button_padding.y * 2) - list_margins.y - i * button_inner_margins };
        if (is_scrollbar) {
            label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
        }
        spawnButton.zext.text = labels[i].text;
        spawnButton.element.position = label_position;
        const ecs_entity_t button = spawn_button(world, &spawnButton);
        if (events && events[i].value) {
            zox_set(button, ClickEvent, { events[i].value })
        }
        children->value[list_start + i] = button;
        zox_add_tag(button, ZextLabel)
    }
    zox_set(e, Children, { children->length, children->value })
    // zox_modified(e, Children)
#ifdef zoxel_include_players
    if (!headless && elements_count > 0 && player) {
        const byte device_mode = zox_get_value(player, DeviceMode)
        if (device_mode == zox_device_mode_gamepad) {
            raycaster_select_element(world, player, children->value[list_start]);
        }
    }
#endif
    return e;
}

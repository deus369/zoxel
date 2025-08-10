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
        int txt_size = labels && labels[i].text ? strlen(labels[i].text) : 0;
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
entity spawn_ui_list(
    ecs *world,
    const entity prefab,
    const entity canvas,
    const char *header_label,
    const int elements_count,
    const int max_elements,
    const text_group* labels,
    const ClickEvent* click_events,
    const SlideEvent* slide_events,
    const byte* types,
    int2 pixel_position,
    const float2 anchor,
    const byte is_close_button,
    byte header_font_size,
    byte font_size,
    const byte layer,
    const byte is_scrollbar,
    const entity player,
    const int2 min_size
) {

    const entity parent = canvas;
    const byte is_header = 1;
    const byte list_start = is_header + is_scrollbar;
    const int children_length = (list_start + elements_count);
    const int scaled_font_size = (int) font_size;   // zox_ui_scale *
    const int scaled_header_font_size = (int) header_font_size; // zox_ui_scale *
    const int scrollbar_width = 36; // * zox_ui_scale;
    const int scrollbar_margins = 8; //  * zox_ui_scale;
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
    int window_width = get_max_width(header_label, scaled_header_font_size, header_padding_x, labels, elements_count, scaled_font_size, button_padding.x + list_margins.x);
    int window_height = (scaled_font_size + button_padding.y * 2) * max_elements + button_inner_margins * (max_elements - 1) + list_margins.y * 2;
    if (min_size.x) {
        window_width = int_max(min_size.x, window_width);
    }
    if (min_size.y) {
        window_height = int_max(min_size.y, window_height);
    }


    int2 pixel_size = { window_width, window_height };


    if (is_scrollbar) {
        pixel_size.x += (scrollbar_width / 2) + scrollbar_margins;
        anchor_element_position2D_with_header(&pixel_position, anchor, pixel_size, header_height);
    }
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);



    zox_instance(prefab);
    zox_name("ui_list");
    zox_set(e, ListUIMax, { max_elements });
    zox_set(e, ElementFontSize, { font_size });
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
    initialize_Children(children, children_length);
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
        const entity scrollbar = spawn_scrollbar(
            world,
            e,
            canvas,
            (int2) { -(scrollbar_width / 2) - scrollbar_margins, 0 },
            header_layer,
            pixel_position_global,
            pixel_size,
            scrollbar_width,
            scrollbar_margins,
            canvas_size,
            max_elements,
            elements_count);
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

        spawnButton.element.render_disabled = !(i >= 0 && i < max_elements);

        int2 position = (int2) {
            0,
            (int) (pixel_size.y / 2) - (i + 0.5f) * (scaled_font_size + button_padding.y * 2) - list_margins.y - i * button_inner_margins
        };

        if (is_scrollbar) {
            position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
        }

        byte spawn_type = 0;
        if (types) {
            spawn_type = types[i];
        }

        spawnButton.element.position = position;
        if (spawn_type == 0) {

            // BUTTONS

            if (labels) {
                spawnButton.zext.text = labels[i].text;
            }
            const entity e2 = spawn_button(world,
                spawnButton.canvas,
                spawnButton.parent,
                spawnButton.element,
                spawnButton.zext,
                spawnButton.button);
            if (click_events && click_events[i].value) {
                zox_set(e2, ClickEvent, { click_events[i].value })
            }
            children->value[list_start + i] = e2;
            zox_add_tag(e2, ZextLabel)

        } else {

            // SLIDERS

            ElementSpawnData spawn_slider_data = spawnButton.element;
            spawn_slider_data.prefab = prefab_slider;
            spawn_slider_data.size = (int2) { 256, 42 };
            SpawnSliderData slider_data = (SpawnSliderData) {
                .prefab_handle = prefab_handle,
                .type = zox_slider_type_float,
                .name = labels[i - 1].text,
                .value = 0.5f,
                .bounds = (float2) { 0, 1 },    // todo: pass this in from setting
            };
            const entity2 e2 = spawn_slider(world,
                spawnButton.canvas,
                spawnButton.parent,
                spawn_slider_data,
                slider_data);
            if (slide_events && slide_events[i].value) {
                zox_set(e2.y, SlideEvent, { slide_events[i].value })
            }
            children->value[list_start + i] = e2.x;

        }
    }
    zox_set(e, Children, { children->length, children->value })
    // zox_modified(e, Children)
    if (!headless && elements_count > 0 && player) {
        const byte device_mode = zox_get_value(player, DeviceMode)
        if (device_mode == zox_device_mode_gamepad) {
            raycaster_select_element(world, player, children->value[list_start]);
        }
    }
    return e;
}
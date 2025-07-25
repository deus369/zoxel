// todo: use spawn_icon_grid for all user menus
// todo: spawn a body ui (as regular element) for icons
// todo: fetch highest layer from canvas? save it refreshing stack when spawning a new window
// todo: prefab_inventory_menu - child prefab of game_icon_window?

ecs_entity_t spawn_prefab_window_users(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("window_users")
    zox_prefab_set(e, FramePrefabLink, { prefab_frame })
    return e;
}

ecs_entity_t spawn_window_users(ecs_world_t *world, SpawnWindowUsers *data) {
    const ecs_entity_t character = data->window.character;
    if (!zox_has_id(character, data->window.user_links_id)) {
        zox_log(" ! character [%lu] has no [%s], cannot spawn ui", character, zox_get_name(data->window.user_links_id))
        return 0;
    }
    // zox_log(" +  character [%lu] inventory has %i slots\n", character, inventory->length)
    const byte body_layer = data->element.layer + 1;
    const byte icon_layer = body_layer + 1;
    const byte is_header = data->window.prefab_header != 0;
    int2 position = data->element.position;
    byte header_height = 0;
    if (is_header) {
        header_height = data->header_zext.font_size + data->header.margins;
    }
    const int2 canvas_position = get_element_pixel_position_global(data->parent.position, data->element.size, position, data->element.anchor);
    const float2 real_position = get_element_position(canvas_position, data->canvas.size);
    anchor_element_position2D(&position, data->element.anchor, data->element.size);
    zox_instance(data->element.prefab)
    zox_set_name(e, data->header_zext.text)
    // zox_set_unique_name(e, data->header_zext.text)
    initialize_element(world, e, data->parent.e, data->canvas.e, position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, canvas_position);
    set_window_bounds_to_canvas(world, e, data->canvas.size, data->element.size, data->element.anchor);
    const UserLinks *user_data = zox_get_id(character, data->window.user_links_id)
    const int user_datas_count = user_data->length;
    const int grid_elements_count = user_datas_count; // data->window.grid_size.x * data->window.grid_size.y
    const int children_length = 1 + is_header;
    // zox_get_muter(e, Children, children)
    Children *children = &((Children) { 0, NULL });
    initialize_memory_component(Children, children, ecs_entity_t, children_length)
    if (children->length != children_length) {
        zox_log(" ! failed to iniitalize children\n")
        return e;
    }
    int2 header_size = int2_zero;
    if (is_header) {
        const byte header_layer = data->element.layer + 1; // 3;
        const float2 header_anchor = (float2) { 0.5f, 1.0f };
        const int2 header_position = (int2) { 0, -header_height / 2 };
        header_size = (int2) { data->element.size.x, header_height };
        // zox_set(e, HeaderHeight, { header_size.y })
        // todo: pass more of t this in from top
        SpawnHeader spawnHeader = {
            .canvas = data->canvas,
            .parent = {
                .e = e,
                .position = canvas_position,
                .size = data->element.size
            },
            .element = {
                .prefab = data->window.prefab_header,
                .layer = header_layer,
                .anchor = header_anchor,
                .position = header_position,
                .size = header_size
             },
            .zext = data->header_zext,
            .header = data->header
        };
        children->value[0] = spawn_header2(world, &spawnHeader);
    }

    // todo:
    //  - fill in element data
    //  - set window prefab as invisible (since im only showing header/panel combo)

    // spawn body
    int2 body_size = int2_sub(data->element.size, (int2) { 0, header_size.y });
    int2 body_position = (int2) { 0, -header_size.y / 2 };
    ElementSpawn spawn_body_data = {
        .canvas = data->canvas,
        .parent = {
            .e = e,
            .position = canvas_position,
            .size = data->element.size
        },
        .element = {
            .prefab = prefab_body,
            .layer = body_layer,
            .anchor = float2_half,
            .position = body_position,
            .size = body_size
        },
        .texture = {
            .fill_color = window_fill,
            .outline_color = window_outline
        }
    };
    const ecs_entity_t body = spawn_element(world, &spawn_body_data);
    children->value[is_header] = body;
    // zox_get_muter(body, Children, body_children)
    Children *body_children = &((Children) { 0, NULL });
    initialize_memory_component(Children, body_children, ecs_entity_t, grid_elements_count)
    int item_index = 0;
    int array_index = 0;
    const byte active_states = zox_has(data->frame.prefab, ActiveState);
    for (int j = data->window.grid_size.y - 1; j >= 0; j--) {
        if (array_index >= body_children->length) {
            break;
        }
        for (int i = 0; i < data->window.grid_size.x; i++) {
            if (array_index >= body_children->length) {
                break;
            }
            const int2 position = {
                (int) ((i - (data->window.grid_size.x / 2.0f) + 0.5f) * (data->window.icon_size + data->window.grid_padding)),
                (int) ((j - (data->window.grid_size.y / 2.0f) + 0.5f) * (data->window.icon_size + data->window.grid_padding))
            };
            SpawnFrame spawnFrame = {
                .canvas = data->canvas,
                .icon = data->icon,
                .parent = {
                    .e = body,
                    .position = spawn_body_data.element.position_in_canvas,
                    .size = spawn_body_data.element.size
                },
                .element = {
                    .prefab = data->frame.prefab,
                    .position = position,
                    .size = int2_single(data->window.icon_size),
                    .layer = icon_layer,
                    .anchor = float2_half
                },
                .texture = data->frame.texture
            };
            spawnFrame.icon.index = array_index;
            const ecs_entity_t user_data_element = user_data->value[item_index];
            body_children->value[array_index] = spawn_frame_user(world, &spawnFrame, user_data_element);
            if (i == 0 && active_states) {
                zox_set(body_children->value[array_index], ActiveState, { 1 }) // first one should be active
            }
            array_index++;
            item_index++;
        }
    }
    zox_set(body, Children, { body_children->length, body_children->value })
    zox_set(e, Children, { children->length, children->value })
    // add to characters element links and link to character
    zox_get_muter(character, ElementLinks, elementLinks)
    add_to_ElementLinks(elementLinks, e);
    zox_set(e, ElementHolder, { character })
    return e;
}

SpawnWindowUsers get_default_spawn_window_users_data(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t character, const ecs_entity_t canvas, const int2 canvas_size) {
    const byte header_font_size = 26 * zox_ui_scale;
    const byte header_margins = 6 * zox_ui_scale;
    const byte header_height = header_font_size + header_margins * 2;
    const float2 anchor = float2_half;
    const int2 position = position;
    const byte2 grid_size = (byte2) { 4, 4 };
    const int grid_padding = 6 * zox_ui_scale;
    const int grid_margins = 16 * zox_ui_scale;
    const int frame_size = default_frame_size * zox_ui_scale;
    const int icon_size = default_icon_size * zox_ui_scale;
    const int2 size = (int2) { grid_padding + (frame_size + grid_padding) * grid_size.x + grid_margins * 2, grid_padding + (frame_size + grid_padding) * grid_size.y + grid_margins * 2 + header_height };
    ecs_entity_t prefab_frame_ = prefab_frame;
    if (zox_has(prefab, FramePrefabLink)) {
        prefab_frame_ = zox_get_value(prefab, FramePrefabLink)
        // zox_log("+ prefab frame found! %s\n", zox_get_name(prefab_frame_))
    } else {
        zox_log("! prefab frame failed! %s\n", zox_get_name(prefab))
    }
    SpawnWindowUsers data = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = canvas,
            .position = int2_half(canvas_size),
            .size = canvas_size,
        },
        .element = {
            .prefab = prefab_window_users,
            .position = int2_zero,
            .size = size,
            .anchor = anchor
        },
        .header = {
            .prefab_zext = prefab_zext,
            .is_close_button = 1,
            .margins = header_margins
        },
        .header_zext = {
            .text = "Users",
            .font_size = header_font_size,
            .font_thickness = 4,
            .font_fill_color = header_font_fill,
            .font_outline_color = header_font_outline
        },
        .frame = {
            .prefab = prefab_frame_,
            .texture = {
                .fill_color = default_fill_color_frame,
                .outline_color = default_outline_color_frame
            }
        },
        .icon = {
            .prefab = prefab_icon,
            .texture = {
                .fill_color = default_fill_color_icon,
                .outline_color = default_outline_color_icon
            },
            .size = icon_size,
            .texture_size = int2_single(default_icon_texture_size)
        },
        .window = {
            .grid_size = grid_size,
            .grid_padding = grid_padding,
            .icon_size = frame_size,
            .character = character,
            .prefab_header = prefab_header,
            // .prefab_header_zext = prefab_zext,
        },
    };
    return data;
}
// todo: use spawn_icon_grid for all user menus
// todo: spawn a body ui (as regular element) for icons
// todo: fetch highest layer from canvas? save it refreshing stack when spawning a new window
// todo: prefab_inventory_menu - child prefab of game_icon_window?
// todo: link to player's character!
//const ecs_entity_t player = zox_get_value(canvas, PlayerLink)
//const ecs_entity_t character = zox_get_value(player, CharacterLink)

ecs_entity_t spawn_prefab_inventory_menu(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_inventory_menu")
    zox_add_tag(e, InventoryMenu)
    prefab_inventory_menu = e;
    return e;
}

ecs_entity_t spawn_inventory_menu2(ecs_world_t *world, SpawnInventoryMenu *data) {
    const unsigned char icon_layer = data->element.layer + 2;
    const unsigned char is_header = data->header.prefab != 0;
    unsigned char header_height = 0;
    if (is_header) header_height = data->header_zext.font_size + data->header.margins;
    const int2 canvas_position = get_element_pixel_position_global(data->parent.position, data->element.size, data->element.position, data->element.anchor);
    const float2 real_position = get_element_position(canvas_position, data->canvas.size);
    zox_instance(data->prefab)
    zox_name("inventory_menu")
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, canvas_position);
    set_window_bounds_to_canvas(world, e, data->canvas.size, data->element.size, data->element.anchor, header_height);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, data->inventory_menu.grid_size.x * data->inventory_menu.grid_size.y + is_header)
    if (is_header) {
        const float2 header_anchor = (float2) { 0.5f, 1.0f };
        const int2 header_position = (int2) { 0, -header_height / 2 };
        const int2 header_size = (int2) { data->element.size.x, header_height };
        // todo: pass more of t this in from top
        SpawnHeader spawnHeader = {
            .canvas = data->canvas,
            .parent = {
                .e = e,
                .position = canvas_position,
                .size = data->element.size
            },
            .element = {
                .layer = data->element.layer + 1,
                .anchor = header_anchor,
                .position = header_position,
                .size = header_size
             },
            .zext = data->header_zext,
            .header = data->header
        };
        children->value[0] = spawn_header2(world, &spawnHeader);
        zox_set(e, HeaderHeight, { header_size.y })
    }
    int array_index = is_header;
    for (int i = 0; i < data->inventory_menu.grid_size.x; i++) {
        for (int j = 0; j < data->inventory_menu.grid_size.y; j++) {
            const int2 position = { (int) ((i - (data->inventory_menu.grid_size.x / 2) + 0.5f) * (data->inventory_menu.icon_size + data->inventory_menu.grid_padding)), (int) ((j - (data->inventory_menu.grid_size.y / 2) + 0.5f) * (data->inventory_menu.icon_size + data->inventory_menu.grid_padding) - header_height / 2) };
            SpawnIconFrame spawnIconFrame = {
                .prefab = prefab_item_icon_frame,
                .canvas = data->canvas,
                .icon_frame = data->icon_frame,
                .icon = data->icon,
                .parent = {
                    .e = e,
                    .position = canvas_position,
                    .size = data->element.size
                },
                .element = {
                    .position = position,
                    .size = int2_single(data->inventory_menu.icon_size),
                    .layer = icon_layer,
                    .anchor = float2_half
                }
            };
            // spawn_element_frame - return ecs_entity_t2
            children->value[array_index] = spawn_icon_frame(world, &spawnIconFrame);
            array_index++;
        }
    }
    zox_modified(e, Children)
    return e;
}

ecs_entity_t spawn_inventory_menu(ecs_world_t *world, const ecs_entity_t canvas) {
    const color frame_fill_color = (color) { 33, 33, 33, 133 };
    const color frame_outline_color = (color) { 33, 33, 33, 133 };
    const color icon_fill_color = (color) { 0, 155, 155, 155 };
    const color icon_outline_color = (color) { 0, 255, 185, 225 };
    const unsigned char header_height = 42;
    const unsigned char header_margins = 16;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const float2 anchor = float2_half;
    const int2 position = position;
    const byte2 grid_size = (byte2) { 4, 4 };
    const int grid_padding = 6;
    const int grid_margins = 16;
    const int icon_size = 64;
    const int2 size = (int2) { grid_padding + (icon_size + grid_padding) * grid_size.x + grid_margins * 2, grid_padding + (icon_size + grid_padding) * grid_size.y + grid_margins * 2 + header_height };
    SpawnInventoryMenu spawnInventoryMenu = {
        .prefab = prefab_inventory_menu,
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
            .position = int2_zero,
            .size = size,
            .anchor = anchor
        },
        .header = {
            .prefab = prefab_header,
            .is_close_button = 1,
            .margins = header_margins
        },
        .header_zext = {
            .prefab = prefab_zext,
            .text = "Inventory",
            .font_size = 28,
            .font_fill_color = header_font_fill_color,
            .font_outline_color = header_font_outline_color
        },
        .inventory_menu = {
            .grid_size = (byte2) { 4, 4 },
            .grid_padding = grid_padding,
            .icon_size = icon_size
        },
        .icon_frame = {
            .fill_color = frame_fill_color,
            .outline_color = frame_outline_color
        },
        .icon = {
            .fill_color = icon_fill_color,
            .outline_color = icon_outline_color
        }
    };
    return spawn_inventory_menu2(world, &spawnInventoryMenu);
}

/*ecs_entity_t spawn_inventory_menu3(ecs_world_t *world, const ecs_entity_t canvas) {
    const color frame_fill_color = (color) { 99, 144, 144, 155 };
    const color window_color = (color) { 66, 35, 25, 255 };
    const unsigned char layer = 0;
    const int icons_x = 4;
    const int icons_y = 4;
    const int padding = 6;
    const int margins = 16;
    const int icon_size = 64;
    const float2 anchor = float2_half;
    const int2 position = int2_zero;
    const int2 icon_size_2 = (int2) { icon_size, icon_size };
    unsigned char is_header = 1;
    const int header_margins = 16;
    unsigned char header_height = 0;
    const int header_font_size = 28;
    if (is_header) {
        header_height = header_font_size + header_margins;
    }
    // rest
    const int2 size = (int2) { padding + (icon_size + padding) * icons_x + margins * 2, padding + (icon_size + padding) * icons_y + margins * 2 + header_height };
    const unsigned char icon_layer = layer + 2;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t parent = canvas;
    const int2 canvas_position = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, position, anchor);
    const float2 position2D = get_element_position(canvas_position, canvas_size);
    zox_instance(prefab_frame_debugger_ui)
    zox_name("inventory_menu")
    initialize_element(world, e, parent, canvas, position, size, size, anchor, layer, position2D, canvas_position);
    set_window_bounds_to_canvas(world, e, canvas_size, size, anchor, header_height);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, icons_x * icons_y + is_header)
    if (is_header) {
        // default header data
        const char *header_label = "Inventory";
        unsigned char is_close_button = 1;
        unsigned char header_layer = 1;
        const float2 header_anchor = (float2) { 0.5f, 1.0f };
        const int2 header_position = (int2) { 0, - header_font_size / 2 - header_margins / 2 };
        const int2 header_size = (int2) { size.x, header_height };
        SpawnHeader spawnHeader = {
            .canvas = {
                .e = canvas,
                .size = canvas_size },
            .parent = {
                .e = e,
                .position = canvas_position,
                .size = size },
            .element = {
                .layer = header_layer,
                .anchor = header_anchor,
                .position = header_position,
                .size = header_size },
            .zext = {
                .prefab = prefab_zext,
                .text = header_label,
                .font_size = header_font_size,
                .font_fill_color = header_font_fill_color,
                .font_outline_color = header_font_outline_color },
            .header = {
                .prefab = prefab_header,
                .is_close_button = is_close_button,
                .margins = header_margins } };
        children->value[0] = spawn_header2(world, &spawnHeader);
        zox_set(e, HeaderHeight, { header_size.y })
    }
    int array_index = is_header;
    for (int i = 0; i < icons_x; i++) {
        for (int j = 0; j < icons_y; j++) {
            const int position_x = (int) ((i - (icons_x / 2) + 0.5f) * (icon_size + padding));
            const int position_y = (int) ((j - (icons_y / 2) + 0.5f) * (icon_size + padding)) - header_height / 2;
            const int2 position = (int2) { position_x, position_y };
            // spawn_element_frame - return ecs_entity_t2
            children->value[array_index] = spawn_element(world, prefab_item_icon_frame, canvas, e, position, icon_size_2, float2_half, icon_layer, frame_fill_color, canvas_position, size);
            array_index++;
        }
    }
    zox_modified(e, Children)
    return e;
}*/

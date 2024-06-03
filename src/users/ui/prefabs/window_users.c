// todo: use spawn_icon_grid for all user menus
// todo: spawn a body ui (as regular element) for icons
// todo: fetch highest layer from canvas? save it refreshing stack when spawning a new window
// todo: prefab_inventory_menu - child prefab of game_icon_window?

// BUG FIX:
// todo: fix crash when closing inventory ui with more items (blank ones)
// todo: it seems to be just the ui breaking on destroy atm

ecs_entity_t spawn_prefab_window_users(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_window_users")
    // zox_add_tag(e, InventoryMenu)
    return e;
}

ecs_entity_t spawn_window_users(ecs_world_t *world, SpawnWindowUsers *data) {
    const ecs_entity_t character = data->window.character;
    if (!zox_has_id(character, data->window.user_links_id)) {
        zox_log(" ! character [%lu] has no inventory, cannot spawn ui\n", character)
        return 0;
    }
    // zox_log(" +  character [%lu] inventory has %i slots\n", character, inventory->length)
    const unsigned char icon_layer = data->element.layer + 2;
    const unsigned char is_header = data->header.prefab != 0;
    unsigned char header_height = 0;
    if (is_header) header_height = data->header_zext.font_size + data->header.margins;
    const int2 canvas_position = get_element_pixel_position_global(data->parent.position, data->element.size, data->element.position, data->element.anchor);
    const float2 real_position = get_element_position(canvas_position, data->canvas.size);
    zox_instance(data->window.prefab)
    zox_name("window_users")
    initialize_element(world, e, data->parent.e, data->canvas.e, data->element.position, data->element.size, data->element.size, data->element.anchor, data->element.layer, real_position, canvas_position);
    set_window_bounds_to_canvas(world, e, data->canvas.size, data->element.size, data->element.anchor, header_height);
    // limit to grid size?
    // todo: FIX THIS LIMIT
    // const ItemLinks *inventory = zox_get(character, ItemLinks)
    const UserLinks *user_data = zox_get_id(character, data->window.user_links_id)
    const int user_datas_count = user_data->length;
    const int grid_elements_count = user_datas_count; // data->window.grid_size.x * data->window.grid_size.y
    const int children_length = grid_elements_count + is_header;
    zox_get_mutt(e, Children, children)
    initialize_memory_component(Children, children, ecs_entity_t, children_length)
    if (children->length != children_length) {
        zox_log(" ! failed to iniitalize children\n")
        return e;
    }
    if (is_header) {
        const float2 header_anchor = (float2) { 0.5f, 1.0f };
        const int2 header_position = (int2) { 0, -header_height / 2 };
        const int2 header_size = (int2) { data->element.size.x, header_height };
        zox_set(e, HeaderHeight, { header_size.y })
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
    }
    int item_index = 0;
    int array_index = is_header;
    for (int j = data->window.grid_size.y - 1; j >= 0; j--) {
        for (int i = 0; i < data->window.grid_size.x; i++) {
            if (array_index >= children->length) break;
            const int2 position = { (int) ((i - (data->window.grid_size.x / 2) + 0.5f) * (data->window.icon_size + data->window.grid_padding)), (int) ((j - (data->window.grid_size.y / 2) + 0.5f) * (data->window.icon_size + data->window.grid_padding) - header_height / 2) };
            SpawnIconFrame spawnIconFrame = {
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
                    .size = int2_single(data->window.icon_size),
                    .layer = icon_layer,
                    .anchor = float2_half
                }
            };
            const ecs_entity_t user_data_element = user_data->value[item_index];
            children->value[array_index] = spawn_icon_frame_user(world, &spawnIconFrame, user_data_element).x;
            array_index++;
            item_index++;
        }
        if (array_index >= children->length) break;
    }
    zox_modified(e, Children)
    return e;
}

SpawnWindowUsers get_default_spawn_window_users_data(const ecs_entity_t character, const ecs_entity_t canvas, const int2 canvas_size) {
    const color frame_fill_color = (color) { 33, 33, 33, 133 };
    const color frame_outline_color = (color) { 33, 33, 33, 133 };
    const color icon_fill_color = (color) { 0, 155, 155, 155 };
    const color icon_outline_color = (color) { 0, 255, 185, 225 };
    const unsigned char header_height = 42;
    const unsigned char header_margins = 16;
    const float2 anchor = float2_half;
    const int2 position = position;
    const byte2 grid_size = (byte2) { 4, 4 };
    const int grid_padding = 6;
    const int grid_margins = 16;
    const int icon_size = 64;
    const int2 size = (int2) { grid_padding + (icon_size + grid_padding) * grid_size.x + grid_margins * 2, grid_padding + (icon_size + grid_padding) * grid_size.y + grid_margins * 2 + header_height };
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
            .text = "Users",
            .prefab = prefab_zext,
            .font_size = 28,
            .font_thickness = 4,
            .font_fill_color = header_font_fill_color,
            .font_outline_color = header_font_outline_color
        },
        .icon_frame = {
            .fill_color = frame_fill_color,
            .outline_color = frame_outline_color
        },
        .icon = {
            .prefab = prefab_icon,
            .fill_color = icon_fill_color,
            .outline_color = icon_outline_color
        },
        .window = {
            .prefab = prefab_window_users,
            .grid_size = (byte2) { 4, 4 },
            .grid_padding = grid_padding,
            .icon_size = icon_size,
            .character = character
        },
    };
    return data;
}

ecs_entity_t spawn_window_users_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnWindowUsers data = get_default_spawn_window_users_data(character, canvas, canvas_size);
    return spawn_window_users(world, &data);
}

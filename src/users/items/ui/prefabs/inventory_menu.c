// todo: use spawn_icon_grid for all user menus
// todo: spawn a body ui (as regular element) for icons
// todo: fetch highest layer from canvas? save it refreshing stack when spawning a new window
// todo: prefab_inventory_menu - child prefab of game_icon_window?

ecs_entity_t spawn_prefab_inventory_menu(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_inventory_menu")
    zox_add_tag(e, InventoryMenu)
    prefab_inventory_menu = e;
    return e;
}

ecs_entity_t spawn_inventory_menu(ecs_world_t *world, SpawnInventoryMenu *data) {
    const ecs_entity_t character = data->inventory_menu.character;
    if (!zox_has(character, ItemLinks)) {
        zox_log(" ! character [%lu] has no inventory, cannot spawn ui\n", character)
        return 0;
    }
    const ItemLinks *inventory = zox_get(character, ItemLinks)
    zox_log(" +  character [%lu] inventory has %i slots\n", character, inventory->length)
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
    // limit to grid size?
    const unsigned char grid_elements_count = inventory->length; // data->inventory_menu.grid_size.x * data->inventory_menu.grid_size.y
    zox_get_mutt(e, Children, children)
    initialize_memory_component(Children, children, ecs_entity_t, grid_elements_count + is_header)

    // the problem is something using children without checks
    /*for (int i = 0; i < children->length; i++) children->value[i] = 0;
    zox_modified(e, Children)
    return e;*/

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
    for (int j = data->inventory_menu.grid_size.y - 1; j >= 0; j--) {
        for (int i = 0; i < data->inventory_menu.grid_size.x; i++) {
            if (array_index >= children->length) {
                break;
                break;
            }
            const ecs_entity_t item = inventory->value[item_index];
            if (item) {
                const ZoxName *zox_name = zox_get(item, ZoxName)
                if (zox_name) {
                    char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
                    // zox_log("   + spawning item ui [%s]\n", zox_get_name(item))
                    zox_log("   + spawning item ui [%i] [%s]\n", item_index, name_string)
                    free(name_string);
                } else {
                    zox_log("   + spawned item ui [%i] [%lu]\n", item_index, item)
                }
            } else {
                zox_log("   + spawned item blank [%i]\n", item_index)
            }
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
            children->value[array_index] = spawn_icon_frame(world, &spawnIconFrame);
            array_index++;
            item_index++;
        }
    }
    zox_modified(e, Children)
    return e;
}

ecs_entity_t spawn_inventory_menu_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t character = zox_get_value(player, CharacterLink)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
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
            .font_thickness = 4,
            .font_fill_color = header_font_fill_color,
            .font_outline_color = header_font_outline_color
        },
        .inventory_menu = {
            .grid_size = (byte2) { 4, 4 },
            .grid_padding = grid_padding,
            .icon_size = icon_size,
            .character = character
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
    return spawn_inventory_menu(world, &spawnInventoryMenu);
}

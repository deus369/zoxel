// todo: move to actions module
ecs_entity_t spawn_prefab_actionbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("actionbar")
    zox_add_tag(e, Actionbar)
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_actionbar(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 position, const float2 anchor, const unsigned char layer, const unsigned char size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int actions_count = 8;
    const int padding_x = 6;
    const int padding_y = 12;
    const int margins = size / 4; //  16;
    // const color actionbar_color = (color) { 66, 35, 25, 255 };
    const int2 actionbar_size = (int2) { padding_x + (size + padding_x) * actions_count + margins * 2, size + padding_y * 2 };
    ElementSpawn spawn_actionbar = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        // todo: pass in parent info for actionbar
        .parent = {
            .e = parent,
            .position = int2_half(canvas_size),
            .size = canvas_size
        },
        .element = {
            .prefab = prefab,
            .layer = layer,
            .anchor = anchor,
            .position = position,
            .size = actionbar_size,
        },
        .texture = {
            .fill_color = default_fill_color_window,
            .outline_color = default_outline_color_window,
        }
    };
    const ecs_entity_t e = spawn_element(world, &spawn_actionbar);
    zox_prefab_add(e, Children)
    zox_get_muter(e, Children, children)
    initialize_memory_component(Children, children, ecs_entity_t, actions_count)
    const int2 action_frame_size = (int2) { size, size };
    ElementSpawn spawn_frame_data = {
        .canvas = spawn_actionbar.canvas,
        .parent = {
            .e = e,
            .position = position,
            .size = actionbar_size
        },
        .element = {
            .prefab = prefab_icon_frame_action,
            .layer = layer + 1,
            .anchor = float2_half,
            .size = action_frame_size,
        },
        .texture = {
            .fill_color = default_fill_color_frame,
            .outline_color = default_outline_color_frame,
        }
    };
    /*ElementSpawn spawn_icon_data = {
        .canvas = spawn_actionbar.canvas,
        .parent = {
            .size = spawn_frame_data.element.size
        },
        .element = {
            .prefab = prefab_icon_frame_action,
            .layer = layer + 2,
            .anchor = float2_half,
            .size = action_icon_size
        },
        .texture = {
            .fill_color = default_fill_color_icon,
            .outline_color = default_outline_color_icon,
        }
    };*/
    for (int i = 0; i < actions_count; i++) {
        const int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (size + padding_x));
        spawn_frame_data.element.position = (int2) { position_x, 0 };
        const ecs_entity_t frame = spawn_element(world, &spawn_frame_data);
        if (i == 0) zox_set(frame, ActiveState, { 1 }) // first one should be active
        children->value[i] = frame;
        /*if (i <= 7) {
            spawn_icon_data.parent.e = frame;
            spawn_icon_data.parent.position = spawn_frame_data.element.position;

            // texture
            ecs_entity_t test_icon_texture = 0;
            if (i == 0) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("LogoutUI"));
            else if (i == 1) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("StatusUI"));
            else if (i == 2) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("InventoryUI"));
            else if (i == 3) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("EquipUI - Copy"));
            else if (i == 4) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("EquipUI"));
            else if (i == 5) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("SpellsUI"));
            else if (i == 6) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("QuestsUI"));
            else if (i == 7) test_icon_texture = string_hashmap_get(files_hashmap_textures, new_string_data("MapUI"));


            zox_get_muter(frame, Children, frame_children)
            initialize_memory_component(Children, frame_children, ecs_entity_t, 1)
            const ecs_entity_t icon2 = spawn_element(world, &spawn_icon_data);
            frame_children->value[0] = icon2;
            zox_set(icon2, GenerateTexture, { zox_generate_texture_none })
            clone_texture_data(world, icon2, test_icon_texture);
            zox_set(icon2, TextureDirty, { 1 })
        }*/
    }
    return e;
}


// const ecs_entity_t actionbar_ui = spawn_element(world, prefab, canvas, parent, actionbar_position, actionbar_size, actionbar_anchor, 1, actionbar_color, int2_half(canvas_size), canvas_size);
// children->value[i] = spawn_element(world, prefab_icon_frame_action, canvas, actionbar_ui, action_icon_position, action_icon_size, float2_half, 2, action_color, actionbar_position, actionbar_size);

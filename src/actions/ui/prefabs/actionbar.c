// todo: move to actions module
/*ecs_entity_t spawn_prefab_actionbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("actionbar")
    // zox_add_tag(e, Actionbar)
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_actionbar(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 position, const float2 anchor, const byte layer, const byte size) {
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

    // todo: make this spawn window, with a tiny header of 8 pixels (so i can drag around actionbar)
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
            .prefab = prefab_frame_action,
            .layer = layer + 1,
            .anchor = float2_half,
            .size = action_frame_size,
        },
        .texture = {
            .fill_color = default_fill_color_frame,
            .outline_color = default_outline_color_frame,
        }
    };
    for (int i = 0; i < actions_count; i++) {
        const int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (size + padding_x));
        spawn_frame_data.element.position = (int2) { position_x, 0 };
        const ecs_entity_t frame = spawn_element(world, &spawn_frame_data);
        if (i == 0) zox_set(frame, ActiveState, { 1 }) // first one should be active
        children->value[i] = frame;
    }
    return e;
}


ecs_entity_t spawn_actionbar_player(ecs_world_t *world, const ecs_entity_t player) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    // const int2 canvas_size = zox_get_value(canvas, PixelSize)
    return spawn_actionbar(world, prefab_actionbar, canvas, canvas, int2_zero, float2_half, 2, 64);
}*/

// const ecs_entity_t actionbar_ui = spawn_element(world, prefab, canvas, parent, actionbar_position, actionbar_size, actionbar_anchor, 1, actionbar_color, int2_half(canvas_size), canvas_size);
// children->value[i] = spawn_element(world, prefab_frame_action, canvas, actionbar_ui, action_icon_position, action_icon_size, float2_half, 2, action_color, actionbar_position, actionbar_size);

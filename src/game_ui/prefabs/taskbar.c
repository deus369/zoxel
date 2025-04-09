ecs_entity_t spawn_prefab_taskbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("taskbar")
    zox_add_tag(e, Taskbar)
    zox_prefab_add(e, Children)
    return e;
}

// todo: make tooltip function just return a string
byte tooltip_event_taskbar_icon(ecs_world_t *world, const TooltipEventData *data) {
    if (!data->triggered || !zox_has(data->triggered, TooltipText)) {
        zox_log("! issue with ui, on tooltip\n")
        return 0;
    }
    zox_geter(data->triggered, TooltipText, tooltip_text)
    char *result = convert_zext_to_text(tooltip_text->value, tooltip_text->length);
    // char *result = "opens a game ui";
    set_entity_text(world, data->tooltip, result);
    free(result);
    return 1;
}

ecs_entity_t spawn_taskbar(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, const byte layer) {
    byte taskbar_count = hook_taskbars->size;
    int2 position = (int2) { 0, -24 * zox_ui_scale };
    float2 anchor = (float2) { 0.5f, 1 };
    const int frame_size = default_frame_size * zox_ui_scale;
    const int icon_size = default_icon_size * zox_ui_scale;
    const int padding_x = 4 * zox_ui_scale;
    const int padding_y = 4 * zox_ui_scale;
    const int margins = frame_size / 4;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 actionbar_size = (int2) { padding_x + (frame_size + padding_x) * taskbar_count + margins * 2, frame_size + padding_y * 2 };
    ElementSpawn spawn_actionbar = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
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
            .size = actionbar_size
        },
        .texture = {
            .fill_color = default_fill_color_window,
            .outline_color = default_outline_color_window,
        }
    };
    const ecs_entity_t e = spawn_element(world, &spawn_actionbar);
    Children *children = &((Children) { 0, NULL });
    initialize_memory_component(Children, children, ecs_entity_t, taskbar_count)
    ElementSpawn spawn_frame_data = {
        .canvas = spawn_actionbar.canvas,
        .parent = {
            .e = e,
            .position = position,
            .size = actionbar_size
        },
        .element = {
            .prefab = prefab_frame_taskbar,
            .layer = layer + 1,
            .anchor = float2_half,
            .size = int2_single(frame_size),
        },
        .texture = {
            .fill_color = default_fill_color_frame,
            .outline_color = default_outline_color_frame,
        }
    };
    ElementSpawn spawn_icon_data = {
        .canvas = spawn_actionbar.canvas,
        .parent = {
            .size = spawn_frame_data.element.size
        },
        .element = {
            .prefab = prefab_icon,
            .layer = layer + 2,
            .anchor = float2_half,
            .size = int2_single(icon_size)
        },
        .texture = {
            .fill_color = default_fill_color_icon,
            .outline_color = default_outline_color_icon,
        }
    };
    for (int i = 0; i < taskbar_count; i++) {
        const int position_x = (int) ((i - (taskbar_count / 2.0f) + 0.5f) * (frame_size + padding_x));
        spawn_frame_data.element.position = (int2) { position_x, 0 };
        const ecs_entity_t frame = spawn_element(world, &spawn_frame_data);
        children->value[i] = frame;
        Children *frame_children = &((Children) { 0, NULL });
        initialize_memory_component(Children, frame_children, ecs_entity_t, 1)
        spawn_icon_data.parent.e = frame;
        spawn_icon_data.parent.position = spawn_frame_data.element.position;
        const ecs_entity_t icon = spawn_element(world, &spawn_icon_data);
        frame_children->value[0] = icon;
        zox_set(icon, IconIndex, { i })
        // hook data
        hook_taskbar hook = hook_taskbars->data[i];
        taskbar_set_icons(world, canvas, frame, i);
        zox_set(icon, ClickEvent, { &taskbar_button_click_event })
        zox_prefab_set(icon, TooltipEvent, { &tooltip_event_taskbar_icon })
        char tooltip_text[64];
        sprintf(tooltip_text, "toggles a [%s] game ui", ecs_get_name(world, hook.component_id));
        zox_prefab_set(icon, TooltipText, { text_to_zext(tooltip_text) })
        // texture
        char *icon_texture_name = hook.texture_name;
        clone_texture_to_entity(world, icon, icon_texture_name);
        zox_set(frame, Children, { frame_children->length, frame_children->value })
        // Active State
        if (i == 0) {
            zox_set(frame, ActiveState, { 1 })
        }
    }
    zox_set(e, Children, { children->length, children->value })
    return e;
}

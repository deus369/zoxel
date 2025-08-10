const int inspector_component_size_buffer = 128;

void button_event_clicked_inspepctor(
    ecs_world_t *world,
    const ecs_entity_t trigger_entity
) {
    if (!zox_has(trigger_entity, Children)) {
        return;
    }
    const Children *children = zox_get(trigger_entity, Children)
    const ecs_entity_t zext_entity = children->value[0];
    print_entity_zext(world, zext_entity);
    // ecs_entity_t target = zox_get_value(trigger_entity, EntityTarget)
    // zox_log("   > target [%lu]\n", target)
    // editor_select_entity(world, target);
}

/*#define zox_dynamic_component_label(type, component)\
    if (is_component_type_##type(id)) { \
        const component* c = ((const component*) ecs_get_id(world, e, id));\
        if (c) { \
            buffer_index += snprintf(buffer + buffer_index, buffer_size, zox_component_string##_##type(c)); \
        } \
    }*/

void get_component_label(
    ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t component,
    char *buffer
) {
    if (!zox_valid(e) || !zox_valid(component)) {
        zox_logw("invalid e or c in inspector label");
        return;
    }
    const int buffer_size = inspector_component_size_buffer;
    int buffer_index = 0;
    ecs_id_t id = component & ECS_COMPONENT_MASK;
    // ecs_entity_t comp = id & ECS_COMPONENT_MASK;
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "%s", ecs_get_name(world, component));

    #define add_component_label(T)\
        else if (is_component_type_##T(id)) { \
            buffer_index = get_type_label_##T(world, e, id, buffer, buffer_size, buffer_index); \
        }

    if (is_component_type_byte(id)) {
        buffer_index = get_type_label_byte(world, e, id, buffer, buffer_size, buffer_index);
    }
    add_component_label(byte)
    add_component_label(byte2)
    add_component_label(byte3)
    add_component_label(int)
    add_component_label(int2)
    add_component_label(int3)
    add_component_label(int4)
    add_component_label(float)
    add_component_label(float2)
    add_component_label(float3)
    add_component_label(float4)
    add_component_label(float6)
    add_component_label(double)
    add_component_label(lint)
    add_component_label(entity)
    add_component_label(color)
    add_component_label(color_rgb)
    add_component_label(text)
    /*else if (is_component_type_int3(id)) {
        buffer_index = get_type_label_int3(world, e, buffer, buffer_size, buffer_index);
    }
    else if (is_component_type_text(id)) {
        buffer_index = get_type_label_text(world, e, buffer, buffer_size, buffer_index);
    }
    // zox_dynamic_component_label(byte, EntityDirty)
    else zox_dynamic_component_label(byte2, TextPadding)
    else zox_dynamic_component_label(int, ID)
    else zox_dynamic_component_label(int2, DraggingDelta)
    // else zox_dynamic_component_label(int3, int3_stub)
    else zox_dynamic_component_label(int4, DraggableLimits)
    else zox_dynamic_component_label(lint, Seed)
    else zox_dynamic_component_label(float, Brightness)
    else zox_dynamic_component_label(float2, Position2D)
    else zox_dynamic_component_label(float3, Position3D)
    else zox_dynamic_component_label(float4, Rotation3D)
    else zox_dynamic_component_label(float6, Position3DBounds)
    else zox_dynamic_component_label(double, SoundLength)
    else zox_dynamic_component_label(entity, CanvasLink)
    else zox_dynamic_component_label(color, Color)
    else zox_dynamic_component_label(color_rgb, ColorRGB)
    // else zox_dynamic_component_label(zext, ZoxName)*/
    else {
        const EcsComponent* c = (EcsComponent*) ecs_get(world, id, EcsComponent);
        unsigned int component_size = c !=  NULL ? c->size : 0;
        if (!component_size) {
            buffer_index += snprintf(buffer + buffer_index, buffer_size, " [tag]");
        } else {
            buffer_index += snprintf(buffer + buffer_index, buffer_size, " [?]");
        }
    }
    // zox_log("   c [%lu] %s\n", component, buffer)
}

// Recreates our list elements
// sets inspector ui compponents, the inspector ui
void set_inspector_element(
    ecs *world,
    const entity window,
    const entity e
) {
    if (!zox_valid(window) || !zox_valid(e)) {
        return;
    }


    const ecs_type_t* type = ecs_get_type(world, e);
    const ecs_id_t* type_ids = type->array;
    const int components_count = type->count; // int32_t
    const byte is_entity_name_label = 1;
    const byte is_header = 1;
    const byte is_scrollbar = 1;
    const byte list_start = is_header + is_scrollbar;


    const int elements_visible = zox_get_value(window, ListUIMax)
    const int font_size = zox_gett_value(window, ElementFontSize);

    const byte button_layer = 1 + zox_get_value(window, Layer2D)
    zox_geter_value(window, CanvasPosition, int2, layout_position)
    zox_geter_value(window, PixelSize, int2, parent_size)
    zox_geter_value(window, CanvasLink, ecs_entity_t, canvas)
    zox_geter_value(canvas, PixelSize, int2, canvas_size)

    // destroy previous ones
    zox_get_muter(window, Children, children)
    const ecs_entity_t scrollbar = children->value[1];
    for (int j = list_start; j < children->length; j++) {
        if (children->value[j]) {
            zox_delete(children->value[j])
        }
    }

    const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x;
    const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x;
    const byte2 button_padding = (byte2) {
        (int) (font_size * 1.46f),
        (int) (font_size * 0.5f)
    };
    const int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
    const int button_inner_margins = (int) (font_size * 0.5f);

    // set new elements size
    const int labels_count = components_count + is_entity_name_label;
    const int childrens_length = list_start + labels_count;
    resize_memory_component(Children, children, ecs_entity_t, childrens_length)
    resize_window_scrollbar(world, children, parent_size, canvas_size, elements_visible, labels_count);


    if (is_entity_name_label) {
        const int list_index = 0;
        const int child_index = list_start + list_index;
        const byte render_disabled = 0;
        zox_geter(e, ZoxName, zoxName);
        char *text;
        byte did_allocate_text = 0;
        if (zoxName) {
            text = convert_zext_to_text(zoxName->value, zoxName->length);
            if (text) {
                did_allocate_text = 1;
            } else {
                text = "failure";
            }
        } else {
            text = "no name";
        }
        const int2 label_position = get_element_label_position(
            list_index,
            font_size,
            button_padding,
            button_inner_margins,
            parent_size,
            list_margins,
            is_scrollbar,
            scrollbar_width,
            scrollbar_margins);
        const ecs_entity_t list_element = spawn_button_old(
            world,
            window,
            canvas,
            label_position,
            button_padding,
            float2_half,
            text,
            font_size,
            button_layer,
            layout_position,
            parent_size,
            canvas_size,
            render_disabled);
        if (did_allocate_text) {
            free(text);
        }
        children->value[child_index] = list_element;
    }
    for (int i = 0; i < components_count; i++) {
        const ecs_id_t id = type_ids[i];
        const int list_index = is_entity_name_label + i;
        const int child_index = list_start + list_index;
        const byte render_disabled = !(list_index >= 0 && list_index < elements_visible);
        const int2 label_position = get_element_label_position(list_index, font_size, button_padding, button_inner_margins, parent_size, list_margins, is_scrollbar, scrollbar_width, scrollbar_margins);
        ecs_entity_t component = 0;
        // const char *text = ""; // labels->data[i].text
        char text[inspector_component_size_buffer];
        if (zox_is_override(id)) {
            // component = id & ECS_COMPONENT_MASK;
            // get_component_label(world, e, component, text);
            const ecs_entity_t component2 = id & ECS_COMPONENT_MASK;
            int buffer_index = 0;
            buffer_index += snprintf(text + buffer_index, sizeof(text), "override [%s]", ecs_get_name(world, component2));
        } else if (ECS_HAS_ID_FLAG(id, PAIR)) {
            const ecs_entity_t relation = ecs_pair_first(world, id);
            const ecs_entity_t target = ecs_pair_second(world, id);
            int buffer_index = 0;
            buffer_index += snprintf(text + buffer_index, sizeof(text), "pair %s [%lu]", ecs_get_name(world, relation), (long int) target);
        } else {
            component = id & ECS_COMPONENT_MASK;
            get_component_label(world, e, component, text);
        }

        SpawnButton spawnButton = {
            .canvas = {
                .e = canvas,
                .size = canvas_size
            },
            .parent = {
                .e = e,
                .position = layout_position,
                .size = parent_size
            },
            .element = {
                .prefab = prefab_button,
                .position = label_position,
                .layer = button_layer,
                .anchor = float2_half,
                .render_disabled = render_disabled
            },
            .button = {
                .prefab_zext = prefab_zext,
                .fill = button_fill,
                .outline = button_outline,
            },
            .zext = {
                .text = text,
                .font_size = font_size,
                .padding = button_padding,
                .font_resolution = button_font_resolution,
                .font_fill_color = button_font_fill,
                .font_outline_color = button_font_outline,
                .font_thickness = button_font_thickness_fill,
                .font_outline_thickness = button_font_thickness_outline,
            },
        };
        const ecs_entity_t e2 = spawn_button(world,
            spawnButton.canvas,
            spawnButton.parent,
            spawnButton.element,
            spawnButton.zext,
            spawnButton.button);

        zox_add_tag(e2, InspectorLabel)
        zox_add_tag(e2, ZextLabel)
        zox_set(e2, EntityTarget, { e })
        zox_set(e2, ComponentTarget, { component })
        children->value[child_index] = e2;
        // zox_set(list_element, ClickEvent, { click_event.value })
    }
    zox_modified(window, Children)
}
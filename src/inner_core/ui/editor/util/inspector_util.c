const int inspector_component_size_buffer = 128;

void button_event_clicked_inspepctor(ecs_world_t *world, ecs_entity_t trigger_entity) {
    if (!zox_has(trigger_entity, Children)) return;
    const Children *children = zox_get(trigger_entity, Children)
    ecs_entity_t zext_entity = children->value[0];
    print_entity_zext(world, zext_entity);
    // ecs_entity_t target = zox_get_value(trigger_entity, EntityTarget)
    // zox_log("   > target [%lu]\n", target)
    // editor_select_entity(world, target);
}

// like text, sets the list of text onto the ui element list
void set_ui_list_inspector(ecs_world_t *world, Children *children, ecs_entity_t window_entity, int elements_visible, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int labels_count, const ClickEvent click_event, const unsigned char button_layer, const int2 button_padding, const int button_inner_margins, const int font_size, const unsigned char list_start, const int2 list_margins, const unsigned char is_scrollbar, const int scrollbar_width, const int scrollbar_margins, const float2 window_position, const int2 window_pixel_position_global, const int2 window_size, const int2 canvas_size) {
    // refresh elements
    ecs_entity_t canvas = main_canvas;
    const int childrens_length = list_start + labels_count;
    for (int j = list_start; j < children->length; j++) zox_delete(children->value[j]) // destroy previous
    resize_memory_component(Children, children, ecs_entity_t, childrens_length)
    for (int j = 0; j < labels_count; j++) {
        unsigned char render_disabled = !(j >= 0 && j < elements_visible);
        int2 label_position = (int2) { 0, (int) (window_size.y / 2) - (j + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - j * button_inner_margins };
        if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
        ecs_entity_t list_element = spawn_button(world, window_entity, canvas, label_position, button_padding, float2_half, labels->data[j].text, font_size, button_layer, window_pixel_position_global, window_size, canvas_size, render_disabled);
        zox_set(list_element, ClickEvent, { click_event.value })
        zox_prefab_set(list_element, EntityTarget, { entities->data[j] })
        children->value[list_start + j] = list_element;
        // zox_log("   > spawned button [%lu] - [%s]\n", list_element, labels->data[j].text)
    }
    for (int j = 0; j < labels_count; j++) free(labels->data[j].text);
    dispose_text_group_dynamic_array_d(labels);
    dispose_ecs_entity_t_array_d(entities);
}

void add_entity_components(ecs_world_t *world, text_group_dynamic_array_d* labels) {

}

void get_component_label(ecs_world_t *world, ecs_entity_t e, ecs_entity_t component, char *buffer) {
    const int size_of_buffer = inspector_component_size_buffer;
    int buffer_index = 0;
    ecs_id_t id = component & ECS_COMPONENT_MASK;
    // ecs_entity_t comp = id & ECS_COMPONENT_MASK;
    buffer_index += snprintf(buffer + buffer_index, size_of_buffer, "%s", ecs_get_name(world, component));
    if (is_component_type_byte(id)) {
        const EntityDirty *component_byte = ((const EntityDirty*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(byte));
    } else if (is_component_type_int(id)) {
        const ID *component_int = ((const ID*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(int));
    } else if (is_component_type_long_int(id)) {
        const Seed *component_long_int = ((const Seed*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(long_int));
    } else if (is_component_type_float(id)) {
        const Brightness *component_float = ((const Brightness*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(float));
    } else if (is_component_type_double(id)) {
        const SoundLength *component_double = ((const SoundLength*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(double));
    } else if (is_component_type_byte2(id)) {
        const ZextPadding *component_byte2 = ((const ZextPadding*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(byte2));
    }  else if (is_component_type_int2(id)) {
        const DraggingDelta *component_int2 = ((const DraggingDelta*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(int2));
    }  else if (is_component_type_float2(id)) {
        const Position2D *component_float2 = ((const Position2D*) ecs_get_id(world, e, id));
        buffer_index += snprintf(buffer + buffer_index, size_of_buffer, zox_component_string(float2));
    } else {
        const EcsComponent* ecsComponent = (EcsComponent*) ecs_get(world, id, EcsComponent);
        unsigned int component_size = ecsComponent !=  NULL ? ecsComponent->size : 0;
        if (!component_size) buffer_index += snprintf(buffer + buffer_index, size_of_buffer, " [tag]");
        else buffer_index += snprintf(buffer + buffer_index, size_of_buffer, " [?]");
        // unsigned int component_size = ((EcsComponent*) ecs_get_id(world, e, id))->size;
        // int component_size = ((EcsComponent*) ecs_get_id(world, e, ecs_id(EcsComponent)))->size;
        // zox_log("   %s component_size [%u]\n", ecs_get_name(world, component), component_size)
        //const EntityDirty *component_byte = ((const EntityDirty*) ecs_get_id(world, e, id));
        //if (!component_byte) buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
        // const ZoxName *zoxName = ((const ZoxName*) ecs_get_id(world, e, id));
        // if (zoxName) buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " m [%i]", zoxName->length);
        // else buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
        // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " %i: [%s]", zoxName->length, convert_zext_to_text(zoxName->value, zoxName->length))
    }
    // zox_log("   c [%lu] %s\n", component, buffer)
}

// sets inspector ui compponents, the inspector ui
void set_inspector_element(ecs_world_t *world, ecs_entity_t window_entity, ecs_entity_t e) {
    if (!ecs_is_alive(world, window_entity)) return;
    if (!ecs_is_alive(world, e)) return;
    // print_entity(world, e);
    const ecs_type_t *type = ecs_get_type(world, e);
    const ecs_id_t *type_ids = type->array;
    const int components_count = type->count; // int32_t
    const unsigned char is_entity_name_label = 1;
    const unsigned char is_header = 1;
    const unsigned char is_scrollbar = 1;
    const unsigned char list_start = is_header + is_scrollbar;
    Children *children = zox_get_mut(window_entity, Children)
    const ecs_entity_t scrollbar = children->value[1];
    const int elements_visible = zox_get_value(window_entity, ListUIMax)
    const int font_size = default_ui_scale * zox_get_value(window_entity, ElementFontSize)
    const unsigned char button_layer = 1 + zox_get_value(window_entity, Layer2D)
    const int2 window_pixel_position_global = zox_get_value(window_entity, CanvasPosition)
    const int2 window_size = zox_get_value(window_entity, PixelSize)
    const ecs_entity_t canvas = zox_get_value(window_entity, CanvasLink)
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x;
    const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x;
        // todo: put these inside a element style
        const int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        const int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
        const int button_inner_margins = (int) (font_size * 0.5f);
    // destroy previous ones
    for (int j = list_start; j < children->length; j++) zox_delete(children->value[j])
    // set new elements size
    const int labels_count = components_count + is_entity_name_label;
    const int childrens_length = list_start + labels_count;
    resize_memory_component(Children, children, ecs_entity_t, childrens_length)
    resize_window_scrollbar(children, window_size, canvas_size, elements_visible, labels_count);
    if (is_entity_name_label) {
        const int list_index = 0;
        const int child_index = list_start + list_index;
        const unsigned char render_disabled = 0;
        const ZoxName *zoxName = zox_get(e, ZoxName)
        char *text = convert_zext_to_text(zoxName->value, zoxName->length);
        const int2 label_position = get_element_label_position(list_index, font_size, button_padding, button_inner_margins, window_size, list_margins, is_scrollbar, scrollbar_width, scrollbar_margins);
        const ecs_entity_t list_element = spawn_button(world, window_entity, canvas, label_position, button_padding, float2_half, text, font_size, button_layer, window_pixel_position_global, window_size, canvas_size, render_disabled);
        free(text);
        children->value[child_index] = list_element;
    }
    for (int i = 0; i < components_count; i++) {
        const ecs_id_t id = type_ids[i];
        const int list_index = is_entity_name_label + i;
        const int child_index = list_start + list_index;
        const unsigned char render_disabled = !(list_index >= 0 && list_index < elements_visible);
        const int2 label_position = get_element_label_position(list_index, font_size, button_padding, button_inner_margins, window_size, list_margins, is_scrollbar, scrollbar_width, scrollbar_margins);
        ecs_entity_t component = 0;
        // const char *text = ""; // labels->data[i].text
        char text[inspector_component_size_buffer];
        if (!ECS_HAS_ID_FLAG(id, PAIR)) {
            component = id & ECS_COMPONENT_MASK;
            get_component_label(world, e, component, text);
        } else {
            ecs_entity_t relation = ecs_pair_first(world, id);
            ecs_entity_t target = ecs_pair_second(world, id);
            int buffer_index = 0;
            buffer_index += snprintf(text + buffer_index, sizeof(text), "pair %s [%lu]", ecs_get_name(world, relation), (long int) target);
        }
        const ecs_entity_t list_element = spawn_button(world, window_entity, canvas, label_position, button_padding, float2_half, text, font_size, button_layer, window_pixel_position_global, window_size, canvas_size, render_disabled);
        zox_add_tag(list_element, InspectorLabel)
        zox_add_tag(list_element, ZextLabel)
        zox_set(list_element, EntityTarget, { e })
        zox_set(list_element, ComponentTarget, { component })
        children->value[child_index] = list_element;
        // zox_set(list_element, ClickEvent, { click_event.value })
    }
    zox_modified(window_entity, Children)
}

/*else if (ECS_HAS_ID_FLAG(id, TAG)) {
    buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
} */

        // ecs_entity_t name_label = children->value[list_start];
        // set_entity_label_with_zext(world, name_label, zoxName->value, zoxName->length);
    /*for (int i = 0; i < components_count; i++) {
        int label_index = list_start + is_entity_name_label + i;
        if (label_index >= children->length) continue;    // limit for now
        ecs_entity_t component_label = children->value[label_index];
        ecs_entity_t component = 0;
        char buffer[inspector_component_size_buffer];
        ecs_id_t id = type_ids[i];
        if (ECS_HAS_ID_FLAG(id, PAIR)) {
            ecs_entity_t rel = ecs_pair_first(world, id);
            ecs_entity_t tgt = ecs_pair_second(world, id);
            int buffer_index = 0;
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " pair %s [%lu]", ecs_get_name(world, rel), tgt);
        } else {
            component = id & ECS_COMPONENT_MASK;
            // ecs_id_t id2 = comp & ECS_COMPONENT_MASK;
            // test reverse
            // zox_log("   ids? %lu - %lu\n", id, id2)
            get_component_label(world, e, component, buffer);
        }
        // set_entity_label_with_text(world, component_label, buffer);
        zox_set(component_label, EntityTarget, { e })
        zox_set(component_label, ComponentTarget, { component })
    }*/
    /*for (int i = components_count + list_start + 1; i < children->length; i++) {
        ecs_entity_t component_label = children->value[i];
        set_entity_label_with_text(world, component_label, " ");
        zox_set(component_label, EntityTarget, { 0 })
        zox_set(component_label, ComponentTarget, { 0 })
    }*/



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
void set_ui_list_inspector(ecs_world_t *world, Children *children, ecs_entity_t window_entity,
    int elements_visible, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int labels_count,
    const ClickEvent click_event,
    const unsigned char button_layer, const int2 button_padding, const int button_inner_margins, const int font_size,
    const unsigned char list_start, const int2 list_margins,
    const unsigned char is_scrollbar, const int scrollbar_width, const int scrollbar_margins,
    const float2 window_position,  const int2 window_size, const int2 canvas_size) {
    // refresh elements
    int childrens_length = list_start + labels_count;
    for (int j = list_start; j < children->length; j++) zox_delete(children->value[j]) // destroy previous
    resize_memory_component(Children, children, ecs_entity_t, childrens_length)
    for (int j = 0; j < labels_count; j++) {
        unsigned char render_disabled = !(j >= 0 && j < elements_visible);
        int2 label_position = (int2) { 0, (int) (window_size.y / 2) - (j + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - j * button_inner_margins };
        if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
        ecs_entity_t list_element = spawn_button(world, window_entity, label_position, button_padding, float2_half, labels->data[j].text, font_size, button_layer, window_position, window_size, canvas_size, render_disabled);
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

// sets inspector ui compponents
void set_inspector_element(ecs_world_t *world, ecs_entity_t inspector, ecs_entity_t e) {
    if (!ecs_is_alive(world, inspector)) return;
    // print_entity(world, e);

    // const ClickEvent click_event = (ClickEvent) { &button_event_clicked_inspepctor };
    // text_group_dynamic_array_d* labels = create_text_group_dynamic_array_d();

    const ZoxName *zoxName = zox_get(e, ZoxName)
    const Children *insector_children = zox_get(inspector, Children)

    ecs_entity_t name_label = insector_children->value[2];
    set_entity_label_with_zext(world, name_label, zoxName->value, zoxName->length);
    const ecs_type_t *type = ecs_get_type(world, e);
    const ecs_id_t *type_ids = type->array;
    int32_t i, count = type->count;
    for (i = 0; i < count; i ++) {
        int label_index = 3 + i;
        if (label_index >= insector_children->length) continue;    // limit for now
        ecs_entity_t component_label = insector_children->value[label_index];
        int buffer_index = 0;
        char buffer[32];
        ecs_id_t id = type_ids[i];
        if (ECS_HAS_ID_FLAG(id, PAIR)) {
            ecs_entity_t rel = ecs_pair_first(world, id);
            ecs_entity_t tgt = ecs_pair_second(world, id);
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " pair %s [%lu]", ecs_get_name(world, rel), tgt);
        } /*else if (ECS_HAS_ID_FLAG(id, TAG)) {
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
        } */else {
            ecs_entity_t comp = id & ECS_COMPONENT_MASK;
            buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " %s", ecs_get_name(world, comp));
            if (is_component_type_byte(id)) {
                const EntityDirty *component_byte = ((const EntityDirty*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(byte));
            } else if (is_component_type_int(id)) {
                const ID *component_int = ((const ID*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(int));
            } else if (is_component_type_long_int(id)) {
                const Seed *component_long_int = ((const Seed*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(long_int));
            } else if (is_component_type_float(id)) {
                const Brightness *component_float = ((const Brightness*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(float));
            } else if (is_component_type_double(id)) {
                const SoundLength *component_double = ((const SoundLength*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(double));
            } else if (is_component_type_byte2(id)) {
                const ZextPadding *component_byte2 = ((const ZextPadding*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(byte2));
            }  else if (is_component_type_int2(id)) {
                const DraggingDelta *component_int2 = ((const DraggingDelta*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(int2));
            }  else if (is_component_type_float2(id)) {
                const Position2D *component_float2 = ((const Position2D*) ecs_get_id(world, e, id));
                buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), zox_component_string(float2));
            } else {
                const EcsComponent* ecsComponent = (EcsComponent*) ecs_get(world, id, EcsComponent);
                unsigned int component_size = ecsComponent !=  NULL ? ecsComponent->size : 0;
                // unsigned int component_size = ((EcsComponent*) ecs_get_id(world, e, id))->size;
                // int component_size = ((EcsComponent*) ecs_get_id(world, e, ecs_id(EcsComponent)))->size;
                zox_log("   %s component_size [%u]\n", ecs_get_name(world, comp), component_size)
                if (!component_size) buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
                //const EntityDirty *component_byte = ((const EntityDirty*) ecs_get_id(world, e, id));
                //if (!component_byte) buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
                else buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [?]");
                // const ZoxName *zoxName = ((const ZoxName*) ecs_get_id(world, e, id));
                // if (zoxName) buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " m [%i]", zoxName->length);
                // else buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " [tag]");
                // buffer_index += snprintf(buffer + buffer_index, sizeof(buffer), " %i: [%s]", zoxName->length, convert_zext_to_text(zoxName->value, zoxName->length))
            }
        }
        set_entity_label_with_text(world, component_label, buffer);
    }
    for (i = count + 3; i < insector_children->length; i++) {
        ecs_entity_t component_label = insector_children->value[i];
        set_entity_label_with_text(world, component_label, "");
    }
}

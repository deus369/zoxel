// note: not sure why this breaks the first time, maybe flecs table issues?
#ifdef zox_glitch_fix_hierarchy_labels
const byte max_hierarchy_labels = 23;
unsigned is_first_hierarchy_spawn = 1;
#endif
const int hierarchy_max_line_characters = 64;
ecs_entity_t editor_selected;
extern void add_to_labels_voxel_links(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level);
extern void add_to_labels_stat_links(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level);
extern ecs_entity_t prefab_app;
extern ecs_entity_t prefab_window;
extern ecs_entity_t prefab_button;
extern ecs_entity_t prefab_zext;
extern ecs_entity_t prefab_zigel;
extern ecs_entity_t prefab_realm;
extern ecs_entity_t prefab_block;
extern ecs_entity_t prefab_texture;

void add_entity_to_labels(ecs_world_t *world,
    const ecs_entity_t e,
    text_group_dynamic_array_d* labels,
    ecs_entity_t_array_d* entities,
    const int tree_level)
{
    if (!zox_valid(e)) {
        return;
    }
    char *text = malloc(hierarchy_max_line_characters);
    if (!zox_has(e, ZoxName)) {
        snprintf(text, hierarchy_max_line_characters, "[%s]", zox_get_name(e));
    } else {
        zox_geter(e, ZoxName, zox_name)
        char *text2 = convert_zext_to_text(zox_name->value, zox_name->length);
        if (text2) {
            snprintf(text, hierarchy_max_line_characters, "%s", text2);
            free(text2);
        } else {
            snprintf(text, hierarchy_max_line_characters, "[%s]", zox_get_name(e));
        }
    }
    for (int i = 0; i < tree_level; i++) {
        char *temp = strdup(text);
        if (temp) {
            snprintf(text, hierarchy_max_line_characters, "-%s", temp);
            free(temp);
        } else {
            zox_log_error("no temp was created")
        }
    }
    // zox_log("%s made label [%s]", zox_get_name(e), text)
    add_to_text_group_dynamic_array_d(labels, (text_group_dynamic) { text = text });
    add_to_ecs_entity_t_array_d(entities, e);
}

int get_max_characters_d(const char *header_label, text_group_dynamic_array_d* labels) {
    int max_characters = 0; // get max text length out of all of the words
    for (int i = 0; i < labels->size; i++) {
        int txt_size = strlen(labels->data[i].text);
        if (txt_size > max_characters) max_characters = txt_size;
    }
    int header_txt_size = strlen(header_label);
    if (header_txt_size > max_characters) {
        max_characters = header_txt_size;
    }
    return max_characters;
}

void add_entity_children_to_labels(ecs_world_t *world,
    ecs_entity_t e,
    text_group_dynamic_array_d* labels,
    ecs_entity_t_array_d* entities,
    int tree_level)
{
    if (!zox_valid(e)) {
        return;
    }
    add_entity_to_labels(world, e, labels, entities, tree_level);
    if (zox_has(e, Children)) {
        tree_level++;
        zox_geter(e, Children, children)
        for (int i = 0; i < children->length; i++) {
            add_entity_children_to_labels(world, children->value[i], labels, entities, tree_level);
        }
    }
}

void zox_print_entity(ecs_world_t *world, ecs_entity_t e) {
    const ecs_type_t *type = ecs_get_type(world, e);
    const ecs_id_t *type_ids = type->array;
    int32_t i, count = type->count;
    char *type_str = ecs_type_str(world, type);
    zox_log("       > ecs_types: %s\n", type_str)
    free(type_str);
    for (i = 0; i < count; i ++) {
        ecs_id_t id = type_ids[i];
        zox_log("       > ")
        if (ECS_HAS_ID_FLAG(id, PAIR)) {
            ecs_entity_t rel = ecs_pair_first(world, id);
            ecs_entity_t tgt = ecs_pair_second(world, id);
            zox_log(" pair %s [%lu]", ecs_get_name(world, rel), tgt)
        } else {
            ecs_entity_t comp = id & ECS_COMPONENT_MASK;
            zox_log(" %lu", comp)
            zox_log(" %s", ecs_get_name(world, comp))
            // how to print void*, get*/ base type of ->value of component
            // zox_log(" [%i]", ecs_get_id(world, target, id)->value)
            if (is_component_type_byte(id)) {
                const EntityDirty *byte_component = ((const EntityDirty*) ecs_get_id(world, e, id));
                if (byte_component) zox_log(" b [%i]", byte_component->value)
            } else if (is_component_type_long_int(id)) {
                const Seed *long_int_component = ((const Seed*) ecs_get_id(world, e, id));
                if (long_int_component) zox_log(" lu [%lu]", long_int_component->value)
            } else if (is_component_type_int2(id)) {
                const DraggingDelta *int2_component = ((const DraggingDelta*) ecs_get_id(world, e, id));
                if (int2_component) zox_log(" i2 [%ix%i]", int2_component->value.x, int2_component->value.y)
            } else if (is_component_type_int(id)) {
                const ID *int_component = ((const ID*) ecs_get_id(world, e, id));
                if (int_component) zox_log(" i [%i]", int_component->value)
            } else if (is_component_type_float(id)) {
                const Brightness *component_float = ((const Brightness*) ecs_get_id(world, e, id));
                if (component_float) zox_log(" f [%f]", component_float->value)
            } else if (is_component_type_color(id)) {
                const Color *component_ = ((const Color*) ecs_get_id(world, e, id));
                if (component_) zox_log("%s", zox_component_string_color_rgb(component_))
            } else {
                const ZoxName *zoxName = ((const ZoxName*) ecs_get_id(world, e, id));
                //const EntityDirty *byte_component = ((const EntityDirty*) ecs_get_id(world, target, id));
                //if (byte_component) zox_log(" [uknown]")
                if (zoxName) zox_log(" %i: [%s]", zoxName->length, convert_zext_to_text(zoxName->value, zoxName->length))
                // else zox_log(" [tag]")
            }
            /*const long int *value = ((const long int*) ecs_get_id(world, target, id));
            if (value) zox_log(" [%lu]", value)*/
        }
        zox_log("\n")
    }
}

void editor_select_entity(ecs_world_t *world, const ecs_entity_t e) {
    if (editor_selected == e) {
        return;
    }
    editor_selected = e;
    set_inspector_element(world, inspector, e);
}

void button_event_clicked_hierarchy(ecs_world_t *world, const ClickEventData *event) {
    if (!zox_has(event->clicked, Children)) {
        return;
    }
    const ecs_entity_t target = zox_get_value(event->clicked, EntityTarget)
    editor_select_entity(world, target);
}

// like text, sets the list of text onto the ui element list
void set_ui_list_hierarchy(ecs_world_t *world,
    Children *children,
    ecs_entity_t window_entity,
    const ecs_entity_t canvas,
    const int elements_visible,
    text_group_dynamic_array_d* labels,
    ecs_entity_t_array_d* entities,
    int labels_count,
    const ClickEvent click_event,
    const byte button_layer,
    const byte2 button_padding,
    const int button_inner_margins,
    const byte font_size,
    const byte list_start,
    const int2 list_margins,
    const byte is_scrollbar,
    const int scrollbar_width,
    const int scrollbar_margins,
    const float2 window_position,
    const int2 window_pixel_position_global,
    const int2 window_size,
    const int2 canvas_size)
{
    // resize scrollbar
    resize_window_scrollbar(world, children, window_size, canvas_size, elements_visible, labels_count);
    // refresh elements
    const int childrens_length = list_start + labels_count;
    // destroy previous ones
    for (int j = list_start; j < children->length; j++) {
        zox_delete(children->value[j])
    }
    // set new elements size
    resize_memory_component(Children, children, ecs_entity_t, childrens_length)
    for (int j = 0; j < labels_count; j++) {
        const byte render_disabled = !(j >= 0 && j < elements_visible);
        int2 label_position = get_element_label_position(j, font_size, button_padding, button_inner_margins, window_size, list_margins, is_scrollbar, scrollbar_width, scrollbar_margins);
        const ecs_entity_t list_element = spawn_button_old(world, window_entity, canvas, label_position, button_padding, float2_half, labels->data[j].text, font_size, button_layer, window_pixel_position_global, window_size, canvas_size, render_disabled, button_fill);
        zox_set(list_element, ClickEvent, { click_event.value })
        zox_set(list_element, EntityTarget, { entities->data[j] })
        children->value[list_start + j] = list_element;
    }
}
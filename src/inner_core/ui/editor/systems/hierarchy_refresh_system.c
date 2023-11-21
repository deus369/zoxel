extern ecs_entity_t local_realm;
extern ecs_entity_t local_terrain;
extern ecs_entity_t main_player;
extern ecs_entity_t local_character3D;
extern void add_realm_entity_to_labels(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level);
const int hierarchy_max_line_characters = 64;
ecs_entity_t editor_selected;
// note: not sure why this breaks the first time, maybe flecs table issues?
#ifdef zox_glitch_fix_hierarchy_labels
const unsigned char max_hierarchy_labels = 23;
unsigned is_first_hierarchy_spawn = 1;
#endif

void add_entity_to_labels(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!e) return;
    char *text = malloc(hierarchy_max_line_characters);
    if (!zox_has(e, ZoxName)) {
        snprintf(text, hierarchy_max_line_characters, "_%lu [%i]", e, tree_level);
    } else {
        const ZoxName *zoxName = zox_get(e, ZoxName)
        char *text2 = convert_zext_to_text(zoxName->value, zoxName->length);
        snprintf(text, hierarchy_max_line_characters, "%s", text2);
        free(text2);
        for (int i = 0; i < tree_level; i++) {
            char *temp = strdup(text);
            snprintf(text, hierarchy_max_line_characters, "-%s", temp);
            free(temp);
        }
    }
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
    if (header_txt_size > max_characters) max_characters = header_txt_size;
    return max_characters;
}

void add_entity_children_to_labels(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int tree_level) {
    if (!e) return;
    add_entity_to_labels(world, e, labels, entities, tree_level);
    if (zox_has(e, Children)) {
        tree_level++;
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) add_entity_children_to_labels(world, children->value[i], labels, entities, tree_level);
    }
}

void print_entity(ecs_world_t *world, ecs_entity_t e) {
    const ecs_type_t *type = ecs_get_type(world, e);
    const ecs_id_t *type_ids = type->array;
    int32_t i, count = type->count;
    char *type_str = ecs_type_str(world, type);
    zox_log("       > ecs_types: %s\n", type_str)
    free(type_str);
    for (i = 0; i < count; i ++) {
        ecs_id_t id = type_ids[i];
        zox_logg("       > ")
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
            } else {
                const ZoxName *zoxName = ((const ZoxName*) ecs_get_id(world, e, id));
                //const EntityDirty *byte_component = ((const EntityDirty*) ecs_get_id(world, target, id));
                //if (byte_component) zox_logg(" [uknown]")
                if (zoxName) zox_log(" %i: [%s]", zoxName->length, convert_zext_to_text(zoxName->value, zoxName->length))
                // else zox_logg(" [tag]")
            }
            /*const long int *value = ((const long int*) ecs_get_id(world, target, id));
            if (value) zox_log(" [%lu]", value)*/
        }
        zox_logg("\n")
    }
}

void editor_select_entity(ecs_world_t *world, ecs_entity_t e) {
    if (editor_selected == e) return;
    editor_selected = e;
    set_inspector_element(world, inspector, e);
}

void button_event_clicked_hierarchy(ecs_world_t *world, ecs_entity_t trigger_entity) {
    if (!zox_has(trigger_entity, Children)) return;
    // const Children *children = zox_get(trigger_entity, Children)
    // ecs_entity_t zext_entity = children->value[0];
    // print_entity_zext(world, zext_entity);
    ecs_entity_t target = zox_get_value(trigger_entity, EntityTarget)
    // zox_log("   > target [%lu]\n", target)
    editor_select_entity(world, target);
}

// like text, sets the list of text onto the ui element list
void set_ui_list_hierarchy(ecs_world_t *world, Children *children, ecs_entity_t window_entity, const ecs_entity_t canvas, const int elements_visible, text_group_dynamic_array_d* labels, ecs_entity_t_array_d* entities, int labels_count, const ClickEvent click_event, const unsigned char button_layer, const int2 button_padding, const int button_inner_margins, const unsigned char font_size, const unsigned char list_start, const int2 list_margins, const unsigned char is_scrollbar, const int scrollbar_width, const int scrollbar_margins, const float2 window_position, const int2 window_pixel_position_global, const int2 window_size, const int2 canvas_size) {
    // resize scrollbar
    resize_window_scrollbar(children, window_size, canvas_size, elements_visible, labels_count);
    // refresh elements
    const int childrens_length = list_start + labels_count;
    // destroy previous ones
    for (int j = list_start; j < children->length; j++) zox_delete(children->value[j])
    // set new elements size
    resize_memory_component(Children, children, ecs_entity_t, childrens_length)
    for (int j = 0; j < labels_count; j++) {
        unsigned char render_disabled = !(j >= 0 && j < elements_visible);
        int2 label_position = get_element_label_position(j, font_size, button_padding, button_inner_margins, window_size, list_margins, is_scrollbar, scrollbar_width, scrollbar_margins);
        const ecs_entity_t list_element = spawn_button(world, window_entity, canvas, label_position, button_padding, float2_half, labels->data[j].text, font_size, button_layer, window_pixel_position_global, window_size, canvas_size, render_disabled);
        zox_set(list_element, ClickEvent, { click_event.value })
        zox_set(list_element, EntityTarget, { entities->data[j] })
        // zox_prefab_set(list_element, EntityTarget, { entities->data[j] })
        children->value[list_start + j] = list_element;
    }
}


// todo: when resize ui, reposition based on parent element (or canvas) and anchoring
void HierarchyRefreshSystem(ecs_iter_t *it) {
    const unsigned char is_header = 1;
    const unsigned char is_scrollbar = 1;
    const unsigned char list_start = is_header + is_scrollbar;
    zox_iter_world()
    zox_field_in(Position2D, position2Ds, 2)
    zox_field_in(CanvasPosition, canvasPositions, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    zox_field_in(Anchor, anchors, 5)
    zox_field_in(ListUIMax, listUIMaxs, 6)
    zox_field_in(ElementFontSize, elementFontSizes, 7)
    zox_field_in(CanvasLink, canvasLinks, 8)
    zox_field_out(HierarchyUIDirty, hierarchyUIDirtys, 9)
    zox_field_out(PixelPosition, pixelPositions, 10)
    zox_field_out(PixelSize, pixelSizes, 11)
    zox_field_out(TextureSize, textureSizes, 12)
    zox_field_out(Children, childrens, 13)
    for (int i = 0; i < it->count; i++) {
        const ecs_entity_t e = it->entities[i];
        zox_field_i_out(HierarchyUIDirty, hierarchyUIDirtys, hierarchyUIDirty)
        if (!hierarchyUIDirty->value) continue;
        zox_field_i_out(Children, childrens, children)
        // if (!children->value) zox_log("    > hierarchy ui is null [%lu]\n", e)
        if (!children->value || children->length < 2) continue; // children issues
        const ecs_entity_t scrollbar = children->value[1];
        if (!scrollbar) continue; // no scrollbar
        const ecs_entity_t header = children->value[0];
        zox_field_i_in(Position2D, position2Ds, position2D)
        zox_field_i_in(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i_in(Layer2D, layer2Ds, layer2D)
        zox_field_i_in(Anchor, anchors, anchor)
        zox_field_i_in(ListUIMax, listUIMaxs, listUIMax)
        zox_field_i_in(ElementFontSize, elementFontSizes, elementFontSize)
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        zox_field_i_out(PixelPosition, pixelPositions, pixelPosition)
        zox_field_i_out(PixelSize, pixelSizes, pixelSize)
        zox_field_i_out(TextureSize, textureSizes, textureSize)
        const ecs_entity_t canvas = canvasLink->value;
        const int2 canvas_size = zox_get_value(canvas, PixelSize)
        const int elements_visible = listUIMax->value;
        const int font_size = elementFontSize->value * default_ui_scale;
        const unsigned char button_layer = layer2D->value + 1;
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x;
        const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x;
        const ClickEvent click_event = (ClickEvent) { &button_event_clicked_hierarchy };
            // todo: put these inside a element style
            const int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
            const int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
            const int button_inner_margins = (int) (font_size * 0.5f);
        // add game entities
        ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(32);
        text_group_dynamic_array_d* labels = create_text_group_dynamic_array_d(32);
        add_realm_entity_to_labels(world, local_realm, labels, entities, 0);
        add_entity_to_labels(world, local_music, labels, entities, 0);
        add_entity_to_labels(world, main_cameras[0], labels, entities, 0);
        add_entity_to_labels(world, ui_cameras[0], labels, entities, 0);
        add_entity_children_to_labels(world, main_player, labels, entities, 0);
        add_entity_children_to_labels(world, keyboard_entity, labels, entities, 0);
        add_entity_children_to_labels(world, mouse_entity, labels, entities, 0);
        add_entity_children_to_labels(world, gamepad_entity, labels, entities, 0);
        add_entity_children_to_labels(world, touchscreen_entity, labels, entities, 0);
        add_entity_children_to_labels(world, local_character3D, labels, entities, 0);
        add_entity_to_labels(world, local_terrain, labels, entities, 0);
        add_entity_children_to_labels(world, canvas, labels, entities, 0);
        // resize window
        int labels_count = labels->size;
        // first pass, limit it, some reason flecs table glitches here
#ifdef zox_glitch_fix_hierarchy_labels
        if (is_first_hierarchy_spawn) { // children->length == 2
            is_first_hierarchy_spawn = 0;
            labels_count = int_min(max_hierarchy_labels, labels_count);
        }
#endif
        const int max_characters = get_max_characters_d("hierarchy", labels);
        const float2 window_position = position2D->value;
        const int2 window_pixel_position_global = canvasPosition->value;
        const int2 old_window_size = pixelSize->value;
        // this resizes the window based on size_x (characters) todo: window resizeable - x/y - variable
        int2 new_window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, old_window_size.y };
        if (is_scrollbar) new_window_size.x += scrollbar_width + scrollbar_margins * 2;
        if (new_window_size.x != old_window_size.x) {
            int header_height = zox_gett_value(header, PixelSize).y;
            reverse_anchor_element_position2D_with_header(&pixelPosition->value, anchor->value, old_window_size, header_height);
            pixelSize->value = new_window_size;
            textureSize->value = new_window_size;
            on_resized_element(world, e, new_window_size, int2_to_float2(canvas_size));
            // set position based on new size
            anchor_element_position2D_with_header(&pixelPosition->value, anchor->value, pixelSize->value, header_height);
        }
        // refresh elements
        set_ui_list_hierarchy(world, children, e, canvas,
            elements_visible, labels, entities, labels_count, click_event,
            button_layer, button_padding, button_inner_margins, font_size,
            list_start, list_margins,
            is_scrollbar, scrollbar_width, scrollbar_margins,
            window_position, window_pixel_position_global, new_window_size, canvas_size);
        // dispose allocated things
        for (int j = 0; j < labels->size; j++) free(labels->data[j].text);
        dispose_text_group_dynamic_array_d(labels);
        dispose_ecs_entity_t_array_d(entities);
        hierarchyUIDirty->value = 0;
    }
} zox_declare_system(HierarchyRefreshSystem)

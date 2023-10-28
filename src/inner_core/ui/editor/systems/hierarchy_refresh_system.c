extern ecs_entity_t local_realm;

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

void add_entity_to_labels(ecs_world_t *world, ecs_entity_t e, text_group_dynamic_array_d* labels, int tree_level) {
    const int line_txt_length = 32;
    unsigned char *text = malloc(line_txt_length);
    if (!zox_has(e, ZoxName)) {
        snprintf(text, line_txt_length, "entity [%lu] [%i]", e, tree_level);
    } else {
        const ZoxName *zoxName = zox_get(e, ZoxName)
        // snprintf(text, line_txt_length, "%s", convert_zext_to_text(zoxName->value, zoxName->length));
        char *text2 = convert_zext_to_text(zoxName->value, zoxName->length);
        snprintf(text, line_txt_length, "%s [%i]", text2, tree_level);
        zox_log("   label: %s: %s\n", text, text2)
        free(text2);
    }
    add_to_text_group_dynamic_array_d(labels, (text_group_dynamic) { text = text });
    if (zox_has(e, Children)) {
        tree_level++;
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) add_entity_to_labels(world, children->value[i], labels, tree_level);
    }
}

void button_event_hierarchy_clicked(ecs_world_t *world, ecs_entity_t trigger_entity) {
    if (!zox_has(trigger_entity, Children)) return;
    const Children *children = zox_get(trigger_entity, Children)
    ecs_entity_t zext_entity = children->value[0];
    print_entity_zext(world, zext_entity);
}

void HierarchyRefreshSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    // const int labels_count = 14;
    const unsigned char is_header = 1;
    const unsigned char is_scrollbar = 1;
    const unsigned char list_start = is_header + is_scrollbar;
    const Position2D *position2Ds = ecs_field(it, Position2D, 2);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 3);
    const ListUIMax * listUIMaxs = ecs_field(it, ListUIMax, 4);
    HierarchyUIDirty *hierarchyUIDirtys = ecs_field(it, HierarchyUIDirty,5);
    PixelSize *pixelSizes = ecs_field(it, PixelSize, 6);
    TextureSize *textureSizes = ecs_field(it, TextureSize, 7);
    Children *childrens = ecs_field(it, Children, 8);
    for (int i = 0; i < it->count; i++) {
        HierarchyUIDirty *hierarchyUIDirty = &hierarchyUIDirtys[i];
        if (!hierarchyUIDirty->value) continue;
        ecs_entity_t e = it->entities[i];
        const Position2D *position2D = &position2Ds[i];
        const Layer2D *layer2D = &layer2Ds[i];
        const ListUIMax *listUIMax = &listUIMaxs[i];
        PixelSize *pixelSize = &pixelSizes[i];
        TextureSize *textureSize = &textureSizes[i];
        Children *children = &childrens[i];
        //Children *children = zox_get_mut(e, Children)
        ecs_entity_t canvas = main_canvas;
        int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
        // spawn extra entities as names
        int elements_visible = zox_get_value(e, ListUIMax)
        // zox_log("   > elements_visible %i\n", elements_visible)
        unsigned char button_layer = layer2D->value + 1;
        int line_txt_length = 16;
        const int font_size = 24 * default_ui_scale;
        int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
        int button_inner_margins = (int) (font_size * 0.5f);
        // scrollbar
        ecs_entity_t scrollbar = children->value[1];
        // const int scrollbar_width = 36 * default_ui_scale;
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x; // 8 * default_ui_scale;
        const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x; // 8 * default_ui_scale;
        ClickEvent clicked_element_event = (ClickEvent) { &button_event_hierarchy_clicked };
        text_group_dynamic_array_d* labels = create_text_group_dynamic_array_d();
        /*for (int j = 0; j < labels_count; j++) {
            unsigned char *text = malloc(line_txt_length);
            snprintf(text, line_txt_length, "entity [%i]", j);
            add_to_text_group_dynamic_array_d(labels, (text_group_dynamic) { text = text });
        }*/
        // children->value[i]
        add_entity_to_labels(world, local_realm, labels, 0);
        int labels_count = labels->size;
        int childrens_length = list_start + labels_count;
        int max_characters = get_max_characters_d("hierarchy", labels);
        int2 window_size = pixelSize->value;
        int2 new_window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, window_size.y };
        if (is_scrollbar) new_window_size.x += scrollbar_width + scrollbar_margins * 2;
        if (new_window_size.x != window_size.x) {
            window_size = new_window_size;
            pixelSize->value = window_size;
            textureSize->value = window_size;
            on_resized_element(world, e, window_size, int2_to_float2(canvas_size));
        }
        // resize scrollbar
        ecs_entity_t scrollbar_front = zox_gett_value(scrollbar, Children)[0];
        int scrollbar_height = (int) window_size.y * ( float_min(1, (float) listUIMax->value / (float) labels_count));
        int2 scrollbar_size = (int2) { zox_gett_value(scrollbar, PixelSize).x, scrollbar_height };
        zox_set(scrollbar_front, PixelSize, { scrollbar_size })
        zox_set(scrollbar_front, TextureSize, { scrollbar_size })
        on_resized_element(world, scrollbar_front, scrollbar_size, int2_to_float2(canvas_size));
        zox_set(scrollbar_front, DraggableLimits, { (int2) { 0, (window_size.y / 2) - scrollbar_height / 2 } })
        zox_set(scrollbar_front, PixelPosition, { (int2) { 0, (window_size.y - scrollbar_height) / 2 } })
        // refresh elements
        for (int j = list_start; j < children->length; j++) zox_delete(children->value[j]) // destroy previous
        resize_memory_component(Children, children, ecs_entity_t, childrens_length)
        for (int j = 0; j < labels_count; j++) {
            unsigned char render_disabled = !(j >= 0 && j < elements_visible);
            int2 label_position = (int2) { 0, (int) (window_size.y / 2) - (j + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - j * button_inner_margins };
            if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
            ecs_entity_t list_element = spawn_button(world, e, label_position, button_padding, float2_half, labels->data[j].text, font_size, button_layer, position2D->value, pixelSize->value, canvas_size, render_disabled);
            zox_set(list_element, ClickEvent, { clicked_element_event.value })
            children->value[list_start + j] = list_element;
            // zox_log("   > spawned button [%lu] - [%s]\n", list_element, labels->data[j].text)
        }
        for (int j = 0; j < labels_count; j++) free(labels->data[j].text);
        dispose_text_group_dynamic_array_d(labels);
        hierarchyUIDirty->value = 0;
    }
} zox_declare_system(HierarchyRefreshSystem)

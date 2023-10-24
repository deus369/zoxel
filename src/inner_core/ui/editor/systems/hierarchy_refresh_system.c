void disable_element_rendering(ecs_world_t *world, ecs_entity_t e, unsigned char disabled) {
    if (!zox_has(e, RenderDisabled)) return;
    RenderDisabled *renderDisabled = zox_get_mut(e, RenderDisabled)
    renderDisabled->value = disabled;
    zox_modified(e, RenderDisabled)
    zox_set(e, RenderDisabled, { disabled })
    if (zox_has(e, Children)) {
        const Children *children = zox_get(e, Children)
        for (int i = 0; i < children->length; i++) disable_element_rendering(world, children->value[i], disabled);
    }
}

void HierarchyRefreshSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const int labels_count = 14;
    const unsigned char is_header = 1;
    const unsigned char is_scrollbar = 1;
    const unsigned char list_start = is_header + is_scrollbar;
    const int childrens_length = list_start + labels_count;
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
        zox_log("   > elements_visible %i\n", elements_visible)
        unsigned char button_layer = layer2D->value + 1;
        int line_txt_length = 16;
        const int font_size = 18 * default_ui_scale;
        int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        int2 list_margins = (int2) { (int) (font_size * 0.2f), (int) (font_size * 0.2f) };
        ecs_entity_t scrollbar = children->value[1];
        // const int scrollbar_width = 36 * default_ui_scale;
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x; // 8 * default_ui_scale;
        const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x; // 8 * default_ui_scale;
        text_group labels[labels_count];
        ClickEvent events[labels_count];
        for (int j = 0; j < labels_count; j++) {
            // labels[i].text = "entity [0]";
            unsigned char *text = malloc(line_txt_length);
            snprintf(text, line_txt_length, "entity [%i]", j);
            labels[j].text = text;
            events[j].value = NULL;
        }
        int max_characters = 0; // get max text length out of all of the words
        for (int j = 0; j < labels_count; j++) {
            int txt_size = strlen(labels[j].text);
            if (txt_size > max_characters) max_characters = txt_size;
        }
        int header_txt_size = strlen("hierarchy");
        if (header_txt_size > max_characters) max_characters = header_txt_size;
        max_characters++;
        int2 window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, (font_size + button_padding.y * 2 + list_margins.y) * listUIMax->value + list_margins.y };
        if (is_scrollbar) window_size.x += (scrollbar_width / 2) + scrollbar_margins;
        if (is_scrollbar) window_size.x += (scrollbar_width / 2) + scrollbar_margins;
        pixelSize->value = window_size;
        textureSize->value = window_size;
        on_resized_element(world, e, window_size, int2_to_float2(canvas_size));
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
        // zox_log("   pre resize children->length %i\n", children->length)
        resize_memory_component(Children, children, ecs_entity_t, childrens_length)
        for (int j = 0; j < labels_count; j++) {
            int2 label_position = (int2) { 0, - j * (font_size + button_padding.y * 2 + list_margins.y) - list_margins.y };
            label_position.y += (pixelSize->value.y - font_size - button_padding.y * 2) / 2;
            if (is_scrollbar) label_position.x -= (scrollbar_width / 2) - scrollbar_margins;
            ecs_entity_t list_element = spawn_button(world, e, label_position, button_padding, float2_half, labels[j].text, font_size, button_layer, position2D->value, pixelSize->value, canvas_size);
            if (events[j].value != NULL) zox_set(list_element, ClickEvent, { events[j].value })
            children->value[list_start + j] = list_element;
            unsigned char render_enabled = j >= 0 && j < elements_visible;
            disable_element_rendering(world, list_element, !render_enabled);
        }
        for (int j = 0; j < labels_count; j++) free(labels[j].text);
        hierarchyUIDirty->value = 0;
    }
} zox_declare_system(HierarchyRefreshSystem)

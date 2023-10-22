void HierarchyRefreshSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    unsigned char is_header = 1;
    unsigned char is_scrollbar = 1;
    unsigned char list_start = is_header + is_scrollbar;
    const Position2D *position2Ds = ecs_field(it, Position2D, 2);
    const Layer2D *layer2Ds = ecs_field(it, Layer2D, 3);
    PixelSize *pixelSizes = ecs_field(it, PixelSize, 4);
    TextureSize *textureSizes = ecs_field(it, TextureSize, 5);
    HierarchyUIDirty *hierarchyUIDirtys = ecs_field(it, HierarchyUIDirty, 6);
    Children *childrens = ecs_field(it, Children, 7);
    for (int i = 0; i < it->count; i++) {
        HierarchyUIDirty *hierarchyUIDirty = &hierarchyUIDirtys[i];
        if (!hierarchyUIDirty->value) continue;
        ecs_entity_t e = it->entities[i];
        const Position2D *position2D = &position2Ds[i];
        const Layer2D *layer2D = &layer2Ds[i];
        PixelSize *pixelSize = &pixelSizes[i];
        TextureSize *textureSize = &textureSizes[i];
        Children *children = &childrens[i];
        ecs_entity_t canvas = main_canvas;
        int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
        // spawn extra entities as names
        unsigned char button_layer = layer2D->value + 1;
        int line_txt_length = 16;
        const unsigned char is_close_button = 1;
        const int font_size = 18;
        const int labels_count = 6;
        int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        int2 list_margins = (int2) { (int) (font_size * 0.2f), (int) (font_size * 0.2f) };
        text_group labels[labels_count];
        ClickEvent events[labels_count];
        // pass in element names
        // take in all non editor element, elements
        for (int j = 0; j < labels_count; j++) {
            // labels[i].text = "entity [0]";
            unsigned char *text = malloc(line_txt_length);
            snprintf(text, line_txt_length, "entity [%i]", j);
            labels[j].text = text;
            events[j].value = NULL;
            // zox_logg(text)
        }
        int max_characters = 0; // get max text length out of all of the words
        for (int j = 0; j < labels_count; j++) {
            int txt_size = strlen(labels[j].text);
            if (txt_size > max_characters) max_characters = txt_size;
        }
        int header_txt_size = strlen("hierarchy");
        if (header_txt_size > max_characters) max_characters = header_txt_size;
        max_characters++;
        int2 window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, (font_size + button_padding.y * 2 + list_margins.y) * labels_count + list_margins.y };
        if (is_scrollbar) window_size.x += font_size / 2;
        pixelSize->value = window_size;
        textureSize->value = window_size;
        for (int j = list_start; j < children->length; j++) zox_delete(children->value[j]) // destroy previous
        resize_memory_component(Children, children, ecs_entity_t, list_start + labels_count)
        for (int j = 0; j < labels_count; j++) {
            int2 label_position = (int2) { 0, - j * (font_size + button_padding.y * 2 + list_margins.y) - list_margins.y };
            label_position.y += (pixelSize->value.y - font_size - button_padding.y * 2) / 2;
            if (is_scrollbar) label_position.x -= font_size / 2;
            ecs_entity_t button = spawn_button(world, e, label_position, button_padding, float2_half, labels[j].text, font_size, button_layer, position2D->value, pixelSize->value, canvas_size);
            if (events[j].value != NULL) zox_set(button, ClickEvent, { events[j].value })
            children->value[list_start + j] = button;
        }
        for (int j = 0; j < labels_count; j++) free(labels[j].text);
        on_resized_element(world, e, pixelSize->value, int2_to_float2(canvas_size));
        // resize header too, after this
        // resize the window size
        hierarchyUIDirty->value = 0;
    }
} zox_declare_system(HierarchyRefreshSystem)

ecs_entity_t prefab_ui_list;

ecs_entity_t spawn_prefab_ui_list(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_ui_list")
    zox_prefab_set(e, ListUIMax, { 0 })
    prefab_ui_list = e;
    return e;
}

ecs_entity_t spawn_ui_list(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t canvas, const char *header_label, int elements_count, int max_elements, const text_group labels[], const ClickEvent events[], int2 position, float2 anchor, unsigned char is_close_button, unsigned char font_size, unsigned char layer) {
    // int spawn_elements_count = min(elements_count, max_elements);
    unsigned char is_header = 1;
    unsigned char is_scrollbar = 1;
    unsigned char list_start = is_header + is_scrollbar;
    int max_characters = 0; // get max text length out of all of the words
    for (int i = 0; i < elements_count; i++) {
        int txt_size = strlen(labels[i].text);
        if (txt_size > max_characters) max_characters = txt_size;
    }
    int header_txt_size = strlen(header_label);
    if (header_txt_size > max_characters) max_characters = header_txt_size;
    float ui_scale = default_ui_scale;
    font_size *= ui_scale;
    const int scrollbar_width = 36 * ui_scale;
    const int scrollbar_margins = 8 * ui_scale;
    int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
    unsigned char header_layer = layer + 1;
    unsigned char button_layer = layer + 1;
    // todo: pass in these properties
    int header_margins = font_size / 3; // 12;
    int header_height = (font_size + header_margins - 1);
    int2 list_margins = (int2) { (int) (font_size * 0.2f), (int) (font_size * 0.2f) };
    int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
    int2 window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, (font_size + button_padding.y * 2 + list_margins.y) * max_elements + list_margins.y };
    if (is_scrollbar) window_size.x += (scrollbar_width / 2) + scrollbar_margins;
    int2 header_position = (int2) { 0, header_height / 2 };
    anchor_position2D(&position, window_size, anchor, header_height);
    zox_instance(prefab)
    zox_name("ui_list")
    zox_set(e, ListUIMax, { max_elements })
    float2 position2D = initialize_ui_components(world, e, canvas, position, window_size, anchor, layer, canvas_size);
    int children_length = (list_start + elements_count);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, children_length)
    if (is_header) children->value[0] = spawn_header(world, e, header_position, (int2) { window_size.x, font_size + header_margins }, (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, header_layer, position2D, window_size, is_close_button, canvas_size);
    if (is_scrollbar) children->value[is_header] = spawn_scrollbar(world, e, (int2) { -(scrollbar_width / 2) - scrollbar_margins, 0 }, header_layer, position2D, window_size, scrollbar_width, scrollbar_margins, canvas_size, elements_count, max_elements);
    for (int i = 0; i < elements_count; i++) {
        int2 label_position = (int2) { 0, - i * (font_size + button_padding.y * 2 + list_margins.y) - list_margins.y };
        label_position.y += (window_size.y - font_size - button_padding.y * 2) / 2;
        if (is_scrollbar) label_position.x -= (scrollbar_width / 2) - scrollbar_margins;
        ecs_entity_t button = spawn_button(world, e, label_position, button_padding, float2_half, labels[i].text, font_size, button_layer, position2D, window_size, canvas_size);
        if (events[i].value) zox_set(button, ClickEvent, { events[i].value })
        children->value[list_start + i] = button;
    }
    zox_modified(e, Children)
    #ifdef zoxel_include_players
        if (!headless && max_elements > 0) select_first_button(world, children->value[list_start]);
    #endif
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned ui list [%lu]\n", e)
    #endif
    return e;
}

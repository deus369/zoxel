extern void button_event_close_window(ecs_world_t *world, ecs_entity_t trigger_entity);
ecs_entity_t header_prefab;

ecs_entity_t spawn_prefab_header(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_header")
    add_ui_plus_components(world, e);
    add_selectable_components(world, e);
    add_draggable_components(world, e);
    zox_add_tag(e, Header)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, Color, {{ 77, 44, 33, 255 }})
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Children, { 0, NULL })
    header_prefab = e;
    return e;
}

ecs_entity_t spawn_close_button(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position_global, int2 parent_size, int2 position, int size, int2 padding, unsigned char layer, int2 canvas_size) {
    const float2 anchor = (float2) { 1, 0.5f };
    ecs_entity_t e = spawn_button(world, parent, canvas, position, padding, anchor, "X", size, layer, pixel_position_global, parent_size, canvas_size, 0);
    zox_set(e, ClickEvent, { &button_event_close_window })
    zox_add_tag(e, CloseButton)
    return e;
}

ecs_entity_t spawn_header(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, int2 pixel_size, float2 anchor, const char* text, int font_size, int header_margins, unsigned char layer, int2 parent_pixel_position_global, int2 parent_pixel_size, unsigned char is_close_button, int2 canvas_size) {
    const int string_length = strlen(text);
    int2 zext_position = (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!is_close_button) {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    const int2 padding = (int2) { (int) (font_size * 0.3f), (int) (font_size * 0.3f) };
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    int children_length = 1;
    if (is_close_button) children_length++;
    const unsigned char child_layer = layer + 1;
    zox_instance(header_prefab)
    zox_name("header")
    zox_set(e, DraggedLink, { parent })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, children_length)
    children->value[0] = spawn_zext(world, prefab_zext, e, canvas, zext_position, zext_anchor, int2_to_byte2(padding), text, font_size, 0, child_layer, pixel_position_global, pixel_size, 0);
    if (is_close_button) {
        int2 close_button_position = (int2) { - (font_size / 2) - header_margins / 2, 0 };
        children->value[1] = spawn_close_button(world, e, canvas, pixel_position_global, pixel_size, close_button_position, font_size, padding, child_layer, canvas_size);
    }
    zox_modified(e, Children)
    return e;
}

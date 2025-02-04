ecs_entity_t spawn_prefab_window_invisible(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("window_invisible")
    add_ui_plus_components_invisible(world, e);
    zox_add_tag(e, Window)
    add_selectable(world, e);
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_add_tag(e, BoundToCanvas)
    zox_prefab_set(e, WindowLayer, { 0 })
    zox_prefab_set(e, SetWindowLayer, { 0 })
    zox_prefab_set(e, HeaderHeight, { 0 })
    // zox_prefab_set(e, ElementFontSize, { 14 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_window")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Window)
    zox_add_tag(e, WindowRaycastTarget)
    add_selectable(world, e);
    add_frame_texture_type(world, e, default_fill_color_window, default_outline_color_window, default_window_corner, default_button_frame_thickness);
    // zox_prefab_set(e, Color, { window_color })
    zox_prefab_set(e, ElementFontSize, { 14 })
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_add_tag(e, BoundToCanvas)
    zox_prefab_set(e, HeaderHeight, { 0 })
    zox_prefab_set(e, WindowLayer, { 0 })
    zox_prefab_set(e, SetWindowLayer, { 0 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 pixel_position, const int2 pixel_size, const float2 anchor, const ecs_entity_t canvas, const unsigned char layer) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const unsigned char header_layer = layer + 1;
    const int font_size = 28;
    const int header_margins = 16;
    const ecs_entity_t parent = canvas;
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    const int2 header_position = (int2) { 0, - font_size / 2 - header_margins / 2 };
    const int2 header_size = (int2) { pixel_size.x, font_size + header_margins};
    const float2 header_anchor = (float2) { 0.5f, 1.0f };
    zox_instance(prefab_window)
    zox_name("window")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    set_window_bounds_to_canvas(world, e, canvas_size, pixel_size, anchor);
    // zox_set(e, HeaderHeight, { header_size.y })
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_header(world, e, canvas, header_position, header_size, header_anchor, header_label, font_size, header_margins, header_layer, pixel_position_global, pixel_size, 1, canvas_size);
    zox_modified(e, Children)
    return e;
}

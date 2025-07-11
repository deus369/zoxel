ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_window")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Window)
    zox_add_tag(e, WindowRaycastTarget)
    add_selectable(world, e);
    // texture
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { default_window_corner })
    zox_prefab_set(e, OutlineThickness, { default_button_frame_thickness })
    zox_prefab_set(e, Color, { default_fill_color_window })
    zox_prefab_set(e, OutlineColor, { default_outline_color_window })
    // ui
    zox_prefab_set(e, ElementFontSize, { 14 })
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_add_tag(e, BoundToCanvas)
    zox_prefab_set(e, HeaderHeight, { 0 })
    zox_prefab_set(e, WindowLayer, { 0 })
    zox_prefab_set(e, SetWindowLayer, { 0 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_window(
    ecs_world_t *world,
    const char *header_label,
    int2 pixel_position,
    const int2 pixel_size,
    const float2 anchor,
    const ecs_entity_t canvas,
    const byte layer)
{
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const byte header_layer = layer + 1;
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
    Children *children = &((Children) { 0, NULL });

    const ecs_entity_t header = spawn_header(world, e, canvas, header_position, header_size, header_anchor, header_label, font_size, header_margins, header_layer, pixel_position_global, pixel_size, 1, canvas_size);
    add_to_Children(children, header);

    zox_set(e, Children, { children->length, children->value })
    return e;
}
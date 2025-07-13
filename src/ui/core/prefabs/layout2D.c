// contains only pixel / transform data - invisible element
// todo: debug tools for these, using line drawing
ecs_entity_t spawn_prefab_layout2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_layout2D")
    // transform2D
    zox_prefab_set(e, Position2D, { { 0, 0 } })
    zox_prefab_set(e, Rotation2D, { 0 })
    zox_prefab_set(e, Scale1D, { 1 })
    // ui components
    zox_add_tag(e, Element)
    zox_prefab_set(e, InitializeElement, { 1 })
    zox_prefab_set(e, PixelPosition, { int2_zero })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, Anchor, { float2_zero })
    zox_prefab_set(e, CanvasLink, { 0 })
    zox_prefab_set(e, Layer2D, { 0 })
    zox_prefab_set(e, CanvasPosition, { int2_zero })
    return e;
}

ecs_entity_t spawn_element_invisible(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent, int2 pixel_position, const int2 pixel_size, const float2 anchor, const byte layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    zox_instance(prefab)
    zox_name("element_invisible")
    initialize_element_invisible(world, e, parent, canvas, pixel_position, pixel_size, anchor, layer, position2D, pixel_position_global);
    return e;
}

ecs_entity_t spawn_element_invisible_on_canvas(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const float2 anchor) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    return spawn_element_invisible(world, prefab, canvas, canvas, pixel_position, pixel_size, anchor, 0, int2_half(canvas_size), canvas_size);
}


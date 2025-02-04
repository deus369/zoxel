ecs_entity_t spawn_prefab_element_basic(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_basic")
    zox_prefab_set(e, Color, { color_white })
    add_components_ui_basic(world, e);
    return e;
}

ecs_entity_t spawn_element_basic(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, int2 position, const int2 pixel_size, const int2 texture_size, const float2 anchor, const unsigned char layer, const int2 parent_position, const int2 parent_size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 position_in_canvas = get_element_pixel_position_global(parent_position, parent_size, position, anchor);
    const float2 position_real = get_element_position(position_in_canvas, canvas_size);
    anchor_element_position2D(&position, anchor, pixel_size);
    zox_instance(prefab_element_basic)
    zox_name("element_basic")
    initialize_element(world, e, parent, canvas, position, pixel_size, texture_size, anchor, layer, position_real, position_in_canvas);
    return e;
}

ecs_entity_t spawn_element_basic_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, const int2 position, const int2 pixel_size, const int2 texture_size, const float2 anchor) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    return spawn_element_basic(world, canvas, canvas, position, pixel_size, texture_size, anchor, 0, int2_half(canvas_size), canvas_size);
}

ecs_entity_t prefab_element_basic;

ecs_entity_t spawn_prefab_element_basic(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_basic")
    zox_prefab_set(e, Color, {{ 255, 255, 255, 255 }})
    add_components_ui_basic(world, e);
    prefab_element_basic = e;
    return e;
}

ecs_entity_t spawn_on_canvas_element_basic(ecs_world_t *world, ecs_entity_t canvas, int2 pixel_position, int2 pixel_size, int2 texture_size, float2 anchor) {
    // return spawn_element(world, canvas, canvas, pixel_position, pixel_size, anchor, 0, (color) { 66, 35, 25, 255 });
    unsigned char layer = 0;
    ecs_entity_t parent = canvas;
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    zox_instance(prefab_element_basic)
    zox_name("element_basic")
    int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, texture_size, anchor, layer, position2D, pixel_position_global);
    return e;
}

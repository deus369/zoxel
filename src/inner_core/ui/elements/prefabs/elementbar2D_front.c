ecs_entity_t prefab_elementbar2D_front;

ecs_entity_t spawn_prefab_elementbar2D_front(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_bar_front2D")
    add_ui_plus_components(world, e);
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, { front_bar_color })
    zox_prefab_set(e, PixelSize, { int2_one })
    zox_prefab_set(e, TextureSize, { int2_one })
    prefab_elementbar2D_front = e;
    return e;
}

ecs_entity_t spawn_elementbar2D_front(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 parent_pixel_position_global, const int2 parent_pixel_size, const int2 canvas_size, const unsigned char layer, const unsigned char render_disabled) {
    const int2 pixel_size = (int2) { 0, parent_pixel_size.y };
    const float2 anchor = float2_half;
    const int2 pixel_position_global = parent_pixel_position_global;
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_elementbar2D_front)
    zox_name("elementbar2D_front")
    initialize_element(world, e, parent, canvas, int2_zero, pixel_size, int2_one, anchor, layer, position2D, pixel_position_global);
    zox_set(e, RenderDisabled, { render_disabled })
    //zox_log(" - spawning pixelbar [%lu] front [%ix%i] at [%ix%i] [%fx%f]\n", e, pixel_size.x, pixel_size.y, pixel_position_global.x, pixel_position_global.y, position2D.x, position2D.y)
    //zox_log(" > spawning pixelbar [%lu]\n", e)
    return e;
}

ecs_entity_t prefab_element_basic;

ecs_entity_t spawn_prefab_element_basic(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element_basic")
    zox_prefab_set(e, Color, {{ 255, 255, 255, 255 }})
    add_components_ui_basic(world, e);
    prefab_element_basic = e;
    return e;
}

ecs_entity_t spawn_element_basic(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, int2 pixel_position, const int2 pixel_size, const int2 texture_size, const float2 anchor, const unsigned char layer, const int2 parent_pixel_position_global, const int2 parent_pixel_size) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    zox_instance(prefab_element_basic)
    zox_name("element_basic")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, texture_size, anchor, layer, position2D, pixel_position_global);
    return e;
}

ecs_entity_t spawn_element_basic_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, const int2 pixel_position, const int2 pixel_size, const int2 texture_size, const float2 anchor) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    return spawn_element_basic(world, canvas, canvas, pixel_position, pixel_size, texture_size, anchor, 0, int2_half(canvas_size), canvas_size);
}


ecs_entity_t spawn_texture_element(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t source_texture, const int2 position, const int2 size) {
    const int2 source_size = zox_get_value(source_texture, TextureSize)
    const TextureData *source_data = zox_get(source_texture, TextureData)
    const ecs_entity_t e = spawn_element_basic_on_canvas(world, canvas, position, size, source_size, float2_zero);
    zox_set(e, TextureDirty, { 1 })
    zox_set(e, TextureData, { source_data->length, source_data->value })
    // zox_set(e, TextureSize, { source_size })
    return e;
}

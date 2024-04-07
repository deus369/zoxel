ecs_entity_t prefab_element;

ecs_entity_t spawn_prefab_element(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_element")
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_prefab_set(e, SelectState, { 0 })
    add_ui_plus_components(world, e);
    prefab_element = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawned prefab element [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, int2 pixel_size, float2 anchor, unsigned char layer, color element_color) {
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    zox_instance(prefab_element)
    int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    anchor_element_position2D(&pixel_position, anchor, pixel_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_set(e, Color, { element_color })
#ifdef zoxel_debug_spawns
    zox_log(" > s   pawned element [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_element_on_canvas(ecs_world_t *world, ecs_entity_t canvas, int2 pixel_position, int2 pixel_size, float2 anchor) {
    return spawn_element(world, canvas, canvas, pixel_position, pixel_size, anchor, 0, (color) { 66, 35, 25, 255 });
}

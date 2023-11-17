ecs_entity_t prefab_canvas_overlay;

ecs_entity_t spawn_prefab_canvas_overlay(ecs_world_t *world) {
    zox_prefab()
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, {{ 33, 33, 33, 255 }})
    zox_prefab_set(e, AnimationState, { 0 })
    zox_prefab_set(e, AnimationStart, { 0 })
    add_ui_plus_components(world, e);
    prefab_canvas_overlay = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawned prefab canvas_overlay [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_canvas_overlay(ecs_world_t *world, ecs_entity_t canvas) {
    ecs_entity_t parent = canvas;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const unsigned char layer = max_render_layers - 1;
    const int2 pixel_position = int2_zero;
    const float2 anchor = float2_half;
    int2 pixel_size = canvas_size;
    zox_instance(prefab_canvas_overlay)
    int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_set(e, AnimationStart, { zox_current_time })
    zox_set(e, AnimationState, { zox_animation_fadeout })
    zox_set(e, Alpha, { 1.0f })
#ifdef zoxel_debug_spawns
    zox_log(" > spawned canvas_overlay [%lu]\n", e)
#endif
    return e;
}

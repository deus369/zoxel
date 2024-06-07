ecs_entity_t spawn_prefab_canvas_overlay(ecs_world_t *world) {
    zox_prefab()
    zox_add_tag(e, CanvasOverlay)
    zox_add_tag(e, FillTexture)
    zox_prefab_set(e, Color, {{ 33, 33, 33, 255 }})
    zox_prefab_set(e, AnimationState, { 0 })
    zox_prefab_set(e, AnimationStart, { 0 })
    zox_prefab_set(e, AnimationLength, { 1.6f})
    zox_prefab_set(e, AnimationDelay, { 0.4f})
    add_ui_plus_components(world, e);
    prefab_add_animation(world, e);
    return e;
}

// todo: stretch to parent size!
ecs_entity_t spawn_canvas_overlay(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const int2 canvas_size) {
#ifdef zox_disable_canvas_overlay
    return 0;
#endif
    const ecs_entity_t parent = canvas;
    const unsigned char layer = max_layers2D - 1;
    const int2 pixel_position = int2_zero;
    const float2 anchor = float2_half;
    const int2 pixel_size = (int2) { 4096, 4096 }; //  canvas_size;
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab)
    zox_name("canvas_overlay")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    // on_child_added(world, canvas, e);
    zox_set(e, Alpha, { 1 })
    trigger_canvas_fade_out(world, e);
    return e;
}

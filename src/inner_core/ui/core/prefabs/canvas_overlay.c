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
    zox_prefab_add(e, AnimationSequence)
    return e;
}

// todo: stretch to parent size!
ecs_entity_t spawn_canvas_overlay(ecs_world_t *world, const ecs_entity_t canvas, const int2 canvas_size) {
    const ecs_entity_t parent = canvas;
    const unsigned char layer = max_layers2D - 1;
    const int2 pixel_position = int2_zero;
    const float2 anchor = float2_half;
    const int2 pixel_size = (int2) { 4096, 4096 }; //  canvas_size;
    const int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(pixel_position_global, canvas_size);
    zox_instance(prefab_canvas_overlay)
    zox_name("canvas_overlay")
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    zox_set(e, Alpha, { 1.0f })
    zox_set(e, AnimationStart, { zox_current_time })
    zox_set(e, AnimationState, { zox_animation_fadeout })
    on_child_added(world, canvas, e);
    return e;
}

void trigger_canvas_fade_transition(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, CanvasOverlay, e)
    if (!e) return;
    zox_set(e, Layer2D, { max_layers2D - 1 })
    // i should add multiple animationions as children or something
    AnimationSequence *animationSequence = zox_get_mut(e, AnimationSequence)
    if (animationSequence->length == 0) {
        resize_memory_component(AnimationSequence, animationSequence, unsigned char, 3)
        animationSequence->value[0] = zox_animation_fadein;
        animationSequence->value[1] = zox_animation_waiting;
        animationSequence->value[2] = zox_animation_fadeout;
        zox_modified(e, AnimationSequence)
    }
    // set start animation
    zox_set(e, AnimationStart, { zox_current_time })
    zox_set(e, AnimationState, { zox_animation_fadein })
    zox_set(e, AnimationLength, { 0.7f})
    zox_set(e, AnimationDelay, { 0.2f})
    zox_set(e, Alpha, { 0.0f })
}

void trigger_canvas_half_fade(ecs_world_t *world, const ecs_entity_t canvas, const float time_length, const float alpha, const unsigned char direction) {
    const float canvas_fade_delay = 0.02f;
    find_child_with_tag(canvas, CanvasOverlay, e)
    if (!e) return;
    zox_set(e, Layer2D, { 0 })
    zox_set(e, RenderDisabled, { 0 })
    // i should add multiple animationions as children or something
    AnimationSequence *animationSequence = zox_get_mut(e, AnimationSequence)
    if (animationSequence->length) {
        resize_memory_component(AnimationSequence, animationSequence, unsigned char, 0)
        zox_modified(e, AnimationSequence)
    }
    // set start animation
    zox_set(e, AnimationStart, { zox_current_time })
    zox_set(e, AnimationState, { zox_animate_alpha })
    zox_set(e, AnimationLength, { time_length - canvas_fade_delay })
    zox_set(e, AnimationDelay, { canvas_fade_delay })
    if (direction) {
        zox_set(e, RenderDisabled, { 0 })
        zox_set(e, AnimateSourceFloat, { 0 })
        zox_set(e, AnimateTargetFloat, { alpha })
    }
    else {
        zox_set(e, AnimateTargetFloat, { 0 })
        zox_set(e, AnimateSourceFloat, { alpha })
    }
}

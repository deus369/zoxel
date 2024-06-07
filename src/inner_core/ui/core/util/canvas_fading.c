const unsigned char pause_ui_overlay_layer = 2;

void clear_animation_sequence(ecs_world_t *world, const ecs_entity_t e) {
    zox_get_muter(e, AnimationSequence, animationSequence)
    if (animationSequence->value) {
        clear_memory_component(AnimationSequence, animationSequence)
        zox_get_muter(e, AnimationTimes, animationTimes)
        clear_memory_component(AnimationTimes, animationTimes)
        zox_get_muter(e, AnimationTargets, animationTargets)
        clear_memory_component(AnimationTargets, animationTargets)
        zox_set(e, AnimationIndex, { 255 })
    }
}

// initial from game start
void trigger_canvas_fade_out(ecs_world_t *world, const ecs_entity_t e) {
    zox_set(e, AnimationStart, { zox_current_time })
    zox_set(e, AnimationState, { zox_animate_alpha })
    zox_set(e, AnimationDelay, { 1.5f })
    zox_set(e, AnimationLength, {  1.5f })
    zox_set(e, AnimateSourceFloat, { 1.0f })
    zox_set(e, AnimateTargetFloat, { 0 })
}

void trigger_canvas_fade_in(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, CanvasOverlay, e)
    clear_animation_sequence(world, e);
    zox_set(e, AnimationState, { zox_animate_alpha })
    zox_set(e, AnimationStart, { zox_current_time })
    zox_set(e, AnimationLength, {  0.7f })
    zox_set(e, AnimationDelay, { 0 })
    zox_set(e, AnimateSourceFloat, { 0 })
    zox_set(e, AnimateTargetFloat, { 1 })
    zox_set(e, RenderDisabled, { 0 })
}

void trigger_canvas_fade_transition(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, CanvasOverlay, e)
    if (!e) {
        zox_log(" ! failed to find canvas_overlay on canvas\n")
        return;
    }
    const float alpha = 1.0f;
    const double fade_time = 0.7;
    const double delay_time = 1.4;
    // zox_log(" + [%lu] triggering fade sequence for canvas_overlay [%lu]\n", canvas, e)
    zox_set(e, Layer2D, { max_layers2D - 1 })
    zox_set(e, AnimationIndex, { 0 })
    zox_set(e, AnimationDelay, { 0 })
    zox_set(e, RenderDisabled, { 0 })
    // i should add multiple animationions as children or something
    zox_get_muter(e, AnimationSequence, animationSequence)
    //if (animationSequence->length == 0) {
    zox_get_muter(e, AnimationTimes, animationTimes)
    zox_get_muter(e, AnimationTargets, animationTargets)
    resize_memory_component(AnimationSequence, animationSequence, unsigned char, 3)
    resize_memory_component(AnimationTimes, animationTimes, double, 3)
    resize_memory_component(AnimationTargets, animationTargets, float, 3)
    animationSequence->value[0] = zox_animate_alpha; // zox_animation_fadein;
    animationTimes->value[0] = fade_time; // zox_animation_fadein;
    animationTargets->value[0] = 1;
    animationSequence->value[1] = zox_animation_waiting;
    animationTimes->value[1] = delay_time; // zox_animation_fadein;
    animationTargets->value[1] = 1;
    animationSequence->value[2] = zox_animate_alpha; // zox_animation_fadeout;
    animationTimes->value[2] = fade_time; // zox_animation_fadein;
    animationTargets->value[2] = 0;
}

void trigger_canvas_half_fade(ecs_world_t *world, const ecs_entity_t canvas, const float time_length, const float alpha, const unsigned char direction) {
    const float canvas_fade_delay = 0.02f;
    find_child_with_tag(canvas, CanvasOverlay, e)
    if (!e) return;
    // zox_log(" + [%lu] triggering half fade for canvas_overlay [%lu]\n", canvas, e)
    zox_set(e, Layer2D, { pause_ui_overlay_layer })
    zox_set(e, RenderDisabled, { 0 })
    // i should add multiple animationions as children or something
    clear_animation_sequence(world, e);
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
        zox_set(e, AnimateSourceFloat, { alpha })
        zox_set(e, AnimateTargetFloat, { 0 })
    }
    //if (direction) zox_set(e, Alpha, { alpha })
    //else zox_set(e, Alpha, { 0 })
}

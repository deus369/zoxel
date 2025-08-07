entity spawn_prefab_canvas_overlay(ecs *world, entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("canvas_overlay")
    zox_add_tag(e, CanvasOverlay)
    // zox_add_tag(e, FillTexture)
    zox_prefab_set(e, AnimationState, { 0 })
    zox_prefab_set(e, AnimationStart, { 0 })
    zox_prefab_set(e, AnimationLength, { 1.6f})
    zox_prefab_set(e, AnimationDelay, { 0.4f})
    // animation
    zox_prefab_set(e, AnimationIndex, { 0 })
    zox_prefab_add(e, AnimationSequence)
    zox_prefab_add(e, AnimationTimes)
    zox_prefab_add(e, AnimationTargets)
    // set
    zox_set(e, Color, { color_black })
    return e;
}
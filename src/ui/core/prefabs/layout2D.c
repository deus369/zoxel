// contains only pixel / transform data - invisible element
// todo: debug tools for these, using line drawing
ecs_entity_t spawn_prefab_layout2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("layout2D")
    // transform2D
    zox_prefab_set(e, Position2D, { { 0, 0 } })
    zox_prefab_set(e, Rotation2D, { 0 })
    zox_prefab_set(e, Scale1D, { 1 })
    // ui components
    zox_add_tag(e, Element)
    zox_prefab_set(e, InitializeElement, { zox_dirty_trigger })
    zox_prefab_set(e, PixelPosition, { int2_zero })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, Anchor, { float2_zero })
    zox_prefab_set(e, CanvasLink, { 0 })
    zox_prefab_set(e, Layer2D, { 0 })
    zox_prefab_set(e, CanvasPosition, { int2_zero })
    return e;
}

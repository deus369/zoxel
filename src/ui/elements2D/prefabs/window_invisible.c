ecs_entity_t spawn_prefab_window_invisible(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("window_invisible")
    zox_add_tag(e, Window)
    add_selectable(world, e);
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_add_tag(e, BoundToCanvas)
    zox_prefab_set(e, WindowLayer, { 0 })
    zox_prefab_set(e, SetWindowLayer, { 0 })
    zox_prefab_set(e, HeaderHeight, { 0 })
    zox_prefab_add(e, Children)
    return e;
}
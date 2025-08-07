entity spawn_prefab_window_invisible(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("window_invisible")
    zox_add_tag(e, Window)
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_add_tag(e, BoundToCanvas)
    zox_prefab_set(e, WindowLayer, { 0 })
    zox_prefab_set(e, SetWindowLayer, { 0 })
    zox_prefab_set(e, HeaderHeight, { 0 })
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}
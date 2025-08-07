entity spawn_prefab_scrollbar_front(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("scrollbar_front")
    zox_add_tag(e, Scrollbar)
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_add_tag(e, Clickable)
    zox_prefab_set(e, ClickState, { 0 })
    zox_prefab_set(e, Clicker, { 0 })
    zox_prefab_set(e, ClickEvent, { NULL })
    zox_add_tag(e, Dragable)
    zox_prefab_set(e, DraggableState, { 0 })
    zox_prefab_set(e, DraggingDelta, { int2_zero })
    zox_prefab_set(e, DraggerLink, { 0 })
    zox_prefab_set(e, DraggedLink, { 0 })
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_set(e, Color, { scrollbar_front_color })
    return e;
}
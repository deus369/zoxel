// just a draggable button left and right only
// just a panel with a label and a bar
// the bar can be clicked to reposition the handle as well
entity spawn_prefab_handle(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("handle")
    // transforms
    zox_prefab_set(e, ParentLink, { 0 })
    // set t texture data
    zox_set(e, FrameCorner, { default_button_corner })
    zox_set(e, OutlineThickness, { default_button_frame_thickness })
    zox_set(e, Color, { default_fill_color })
    zox_set(e, OutlineColor, { default_outline_color })
    // interactable
    zox_add_tag(e, Clickable)
    zox_add_tag(e, Dragable)
    zox_add_tag(e, ClickMakeSound)
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_prefab_set(e, ClickState, { 0 })
    zox_prefab_set(e, Clicker, { 0 })
    zox_prefab_set(e, ClickEvent, { NULL })
    zox_prefab_set(e, DraggableState, { 0 })
    zox_prefab_set(e, DraggingDelta, { int2_zero })
    zox_prefab_set(e, DraggerLink, { 0 })
    zox_prefab_set(e, DraggedLink, { 0 })
    zox_prefab_set(e, DraggableLimits, { int4_zero })
    zox_prefab_set(e, SlideEvent, { 0 })
    zox_prefab_set(e, SlideBounds, { (float2) { 0, 1 }})
    return e;
}
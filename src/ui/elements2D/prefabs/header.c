ecs_entity_t spawn_prefab_header(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("header")
    zox_add_tag(e, Header)
    zox_add_tag(e, WindowRaycastTarget)
    // zox_add_tag(e, TextureAddNoise)
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_add_tag(e, Dragable)
    zox_prefab_set(e, DraggableState, { 0 })
    zox_prefab_set(e, DraggingDelta, { int2_zero })
    zox_prefab_set(e, DraggerLink, { 0 })
    zox_prefab_set(e, DraggedLink, { 0 })
    add_frame_texture_type(world, e, header_fill, header_outline, default_button_corner, default_button_frame_thickness);
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}
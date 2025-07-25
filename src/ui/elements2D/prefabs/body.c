ecs_entity_t spawn_prefab_body(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("body")
    zox_add_tag(e, Body)
    zox_add_tag(e, WindowRaycastTarget)
    add_frame_texture_type(world, e, window_fill, window_outline, default_button_corner, default_button_frame_thickness);
    zox_add_tag(e, Selectable)
    // zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_prefab_add(e, Children)
    return e;
}
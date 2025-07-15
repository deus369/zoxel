ecs_entity_t spawn_prefab_scrollbar(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("scrollbar")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { zox_select_state_none })
    zox_add_tag(e, Clickable)
    zox_prefab_set(e, ClickState, { 0 })
    zox_prefab_set(e, Clicker, { 0 })
    zox_prefab_set(e, ClickEvent, { NULL })
    zox_add_tag(e, Scrollbar)
    zox_prefab_set(e, ElementMargins, { int2_zero })
    add_frame_texture_type(world, e, scrollbar_color, default_outline_color, default_button_corner, default_button_frame_thickness);
    zox_prefab_add(e, Children)
    return e;
}
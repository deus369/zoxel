// just a panel with a label and a bar
// the bar can be clicked to reposition the handle as well
ecs_entity_t spawn_prefab_slider(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("slider")
    // transforms
    zox_prefab_set(e, ParentLink, { 0 })
    // set t texture data
    zox_set(e, FrameCorner, { default_button_corner })
    zox_set(e, OutlineThickness, { default_button_frame_thickness })
    zox_set(e, Color, { default_fill_color })
    zox_set(e, OutlineColor, { default_outline_color })
    return e;
}
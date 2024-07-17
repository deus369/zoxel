ecs_entity_t spawn_prefab_body(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("body")
    zox_add_tag(e, Body)
    zox_add_tag(e, WindowRaycastTarget)
    zox_prefab_add(e, Children)
    add_frame_texture_type(world, e, default_fill_color_window, default_outline_color_window, default_button_corner, default_button_frame_thickness);
    add_selectable(world, e);
    return e;
}

ecs_entity_t spawn_body(ecs_world_t *world, ElementSpawn *data) {
    const ecs_entity_t e = spawn_element(world, data);
    return e;
}

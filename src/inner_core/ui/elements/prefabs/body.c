ecs_entity_t spawn_prefab_body(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("body")
    zox_add_tag(e, Body)
    zox_add_tag(e, WindowRaycastTarget)
    zox_prefab_add(e, Children)
    add_frame_texture_type(world, e, window_color, 7, 6);
    add_selectable(world, e);
    return e;
}

ecs_entity_t spawn_body(ecs_world_t *world, SpawnElement *data) {
    const ecs_entity_t e = spawn_element(world, data);
    return e;
}

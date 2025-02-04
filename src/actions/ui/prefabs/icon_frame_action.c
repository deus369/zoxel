ecs_entity_t spawn_prefab_icon_frame_action(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("icon_frame_action")
    add_activatable_components(world, e);
    zox_add_tag(e, IconLabel)
    return e;
}

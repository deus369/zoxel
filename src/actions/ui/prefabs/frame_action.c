ecs_entity_t spawn_prefab_frame_action(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("frame_action")
    zox_prefab_set(e, ActiveState, { 0 })
    zox_add_tag(e, IconLabel)
    return e;
}
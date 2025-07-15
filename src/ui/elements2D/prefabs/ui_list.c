ecs_entity_t spawn_prefab_ui_list(ecs_world_t *world, ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("ui_list")
    zox_prefab_set(e, ListUIMax, { 0 })
    return e;
}
ecs_entity_t spawn_prefab_statbar2D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("statbar2D")
    zox_add_tag(e, Statbar)
    zox_prefab_set(e, StatLink, { 0 })
    return e;
}
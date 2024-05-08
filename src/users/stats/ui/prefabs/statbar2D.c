ecs_entity_t prefab_statbar2D;

void spawn_prefab_statbar2D(ecs_world_t *world) {
    zox_prefab_child(prefab_elementbar2D)
    zox_prefab_name("prefab_statbar2D")
    zox_add_tag(e, Statbar)
    zox_prefab_set(e, StatLink, { 0 })
    prefab_statbar2D = e;
}

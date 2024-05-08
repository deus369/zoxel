ecs_entity_t prefab_statbar3D;

void spawn_prefab_statbar3D(ecs_world_t *world) {
    zox_prefab_child(prefab_elementbar3D)
    zox_prefab_name("prefab_statbar3D")
    zox_add_tag(e, Statbar)
    zox_prefab_set(e, StatLink, { 0 })
    prefab_statbar3D = e;
}

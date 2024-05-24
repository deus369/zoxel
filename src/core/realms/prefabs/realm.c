ecs_entity_t spawn_prefab_realm(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_realm")
    zox_add_tag(e, Realm)
    zox_prefab_set(e, Colors, { 0, NULL })
    return e;
}

ecs_entity_t spawn_realm(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("realm")
    local_realm = e;
    return e;
}

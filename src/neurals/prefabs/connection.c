ecs_entity_t spawn_prefab_connection(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_connection")
    zox_add_tag(e, Connection)
    zox_prefab_add(e, ConnectionData)
    zox_prefab_set(e, Signal, { 0 })
    zox_prefab_set(e, Transfer, { 0 })
    zox_prefab_set(e, Weight, { 1.0f })
    zox_prefab_set(e, BrainLink, { 0 })
    return e;
}

ecs_entity_t spawn_connection(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t brain, const ecs_entity_t a, const ecs_entity_t b, const float weight) {
    zox_instance(prefab)
    zox_name("connection")
    zox_set(e, ConnectionData, { { a, b } })
    zox_set(e, Weight, { weight })
    zox_set(e, BrainLink, { brain })
    return e;
}

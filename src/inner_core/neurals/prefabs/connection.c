ecs_entity_t prefab_connection;

ecs_entity_t spawn_prefab_connection(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_connection")
    zox_add_tag(e, Connection)
    zox_add(e, ConnectionData)
    zox_prefab_set(e, Signal, { 0 })
    zox_prefab_set(e, SignalStrength, { 0 })
    zox_prefab_set(e, Weight, { 1.0f })
    prefab_connection = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab connection [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_connection(ecs_world_t *world, ecs_entity_t neuronA, ecs_entity_t neuronB, float weight) {
    zox_instance(prefab_connection)
    zox_name("connection")
    zox_set(e, ConnectionData, { { neuronA, neuronB } })
    zox_set(e, Weight, { weight })
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned connection [%lu]\n", (long int) e);
    #endif
    return e;
}
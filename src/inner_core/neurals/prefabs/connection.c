ecs_entity_t prefab_connection;

ecs_entity_t spawn_prefab_connection(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_connection")
    zox_add_tag(e, Connection)
    zox_add(e, ConnectionData)
    zox_set(e, Signal, { 0 })
    zox_set(e, SignalStrength, { 0 })
    zox_set(e, Weight, { 1.0f })
    ecs_defer_end(world);
    prefab_connection = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab connection [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_connection(ecs_world_t *world, ecs_entity_t neuronA, ecs_entity_t neuronB, float weight) {
    ecs_defer_begin(world);
    zox_instance(prefab_connection)
    zox_name("connection")
    zox_set_only(e, ConnectionData, { { neuronA, neuronB } })
    zox_set_only(e, Weight, { weight })
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned connection [%lu]\n", (long int) e);
    #endif
    return e;
}
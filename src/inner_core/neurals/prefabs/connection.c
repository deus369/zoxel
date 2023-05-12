ecs_entity_t prefab_connection;

ecs_entity_t spawn_prefab_connection(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_connection");
    zoxel_add_tag(e, Connection);
    zoxel_add(world, e, ConnectionData);
    zoxel_set(world, e, Signal, { 0 });
    zoxel_set(world, e, SignalStrength, { 0 });
    zoxel_set(world, e, Weight, { 1.0f });
    ecs_defer_end(world);
    prefab_connection = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab connection [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_connection(ecs_world_t *world, ecs_entity_t neuronA, ecs_entity_t neuronB, float weight) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_connection);
    set_unique_entity_name(world, e, "connection");
    ecs_set(world, e, ConnectionData, { { neuronA, neuronB } });
    ecs_set(world, e, Weight, { weight });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned connection [%lu]\n", (long int) e);
    #endif
    return e;
}
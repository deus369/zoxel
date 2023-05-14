ecs_entity_t prefab_stat;

ecs_entity_t spawn_prefab_stat(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_stat");
    zox_add_tag(e, Stat);
    // zox_add(e, ZoxName);
    ecs_defer_end(world);
    prefab_stat = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab stat [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_stat(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_stat);
    set_unique_entity_name(world, e, "stat");
    // ecs_set(world, e, Position3D, { position });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned stat [%lu]\n", (long int) e);
    #endif
    return e;
}
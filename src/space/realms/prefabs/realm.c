ecs_entity_t prefab_realm;

ecs_entity_t spawn_prefab_realm(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, ""); // prefab_realm");
    set_unique_entity_name(world, e, "prefab_realm");
    zoxel_add_tag(world, e, Realm);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab realm [%lu].\n", (long int) (e));
    #endif
    prefab_realm = e;
    return e;
}

ecs_entity_t spawn_realm(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_realm);
    set_unique_entity_name(world, e, "realm");
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned realm [%lu]\n", (long int) e);
    #endif
    return e;
}
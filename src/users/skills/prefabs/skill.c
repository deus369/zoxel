ecs_entity_t prefab_skill;

ecs_entity_t spawn_prefab_skill(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_skill")
    zox_add_tag(e, Skill);
    // zox_add(e, ZoxName);
    ecs_defer_end(world);
    prefab_skill = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab skill [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_skill(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_instance(prefab_skill)
    zox_name("skill")
    // ecs_set(world, e, Position3D, { position });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned skill [%lu]\n", (long int) e);
    #endif
    return e;
}
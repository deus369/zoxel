ecs_entity_t prefab_skill;

ecs_entity_t spawn_prefab_skill(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_skill");
    zoxel_add_tag(e, Skill);
    // zoxel_add(world, e, ZoxName);
    ecs_defer_end(world);
    prefab_skill = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab skill [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_skill(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_skill);
    set_unique_entity_name(world, e, "skill");
    // ecs_set(world, e, Position3D, { position });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned skill [%lu]\n", (long int) e);
    #endif
    return e;
}
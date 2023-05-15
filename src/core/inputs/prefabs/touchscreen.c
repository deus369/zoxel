ecs_entity_t prefab_touchscreen;
ecs_entity_t touchscreen_entity;

ecs_entity_t spawn_prefab_touchscreen(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "touchscreen_prefab");
    zox_add_tag(e, Device);
    zox_set(e, Touchscreen, touchscreen_zero);
    ecs_defer_end(world);
    prefab_touchscreen = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab touchscreen [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_touchscreen(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_touchscreen);
    set_unique_entity_name(world, e, "touchscreen");
    ecs_defer_end(world);
    touchscreen_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned touchscreen [%lu].\n", (long int) (e));
    #endif
    return e;
}
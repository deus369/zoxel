ecs_entity_t prefab_gamepad;
ecs_entity_t gamepad_entity;

ecs_entity_t spawn_prefab_gamepad(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "gamepad_prefab");
    set_unique_entity_name(world, e, "gamepad_prefab");
    zoxel_add_tag(world, e, Device);
    zoxel_set(world, e, Gamepad, { });
    ecs_defer_end(world);
    prefab_gamepad = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab gamepad [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_gamepad(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_gamepad);
    set_unique_entity_name(world, e, "gamepad");
    ecs_defer_end(world);
    gamepad_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned gamepad [%lu].\n", (long int) (e));
    #endif
    return e;
}
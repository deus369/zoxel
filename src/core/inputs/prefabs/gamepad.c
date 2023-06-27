ecs_entity_t prefab_gamepad;
ecs_entity_t gamepad_entity;

ecs_entity_t spawn_prefab_gamepad(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("gamepad_prefab")
    zox_add_tag(e, Device)
    zox_set(e, Gamepad, gamepad_zero)
    ecs_defer_end(world);
    prefab_gamepad = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab gamepad [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_gamepad(ecs_world_t *world) {
    zox_instance(prefab_gamepad)
    zox_name("gamepad")
    gamepad_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned gamepad [%lu].\n", (long int) (e));
    #endif
    return e;
}
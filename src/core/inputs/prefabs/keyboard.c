ecs_entity_t prefab_keyboard;
ecs_entity_t keyboard_entity;

ecs_entity_t spawn_prefab_keyboard(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_keyboard")
    zox_add_tag(e, Device)
    zox_add(e, Keyboard)
    ecs_defer_end(world);
    prefab_keyboard = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab keyboard [%lu]\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_keyboard(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_instance(prefab_keyboard)
    zox_name("keyboard")
    zox_set_only(e, Keyboard, { })  // zeros it out?
    ecs_defer_end(world);
    keyboard_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned mouse [%lu].\n", (long int) (e));
    #endif
    return e;
}
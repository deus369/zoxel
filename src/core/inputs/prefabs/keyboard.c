ecs_entity_t prefab_keyboard;
ecs_entity_t keyboard_entity;

ecs_entity_t spawn_prefab_keyboard(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_keyboard");
    zox_add_tag(e, Device);
    zox_add(e, Keyboard);
    ecs_defer_end(world);
    prefab_keyboard = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab keyboard [%lu]\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_keyboard(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_keyboard);
    set_unique_entity_name(world, e, "keyboard");
    ecs_set(world, e, Keyboard, { });
    ecs_defer_end(world);
    keyboard_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned mouse [%lu].\n", (long int) (e));
    #endif
    return e;
}
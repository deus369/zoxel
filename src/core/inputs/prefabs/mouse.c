ecs_entity_t prefab_mouse;
ecs_entity_t mouse_entity;

ecs_entity_t spawn_prefab_mouse(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_mouse");
    zoxel_add_tag(world, e, Device);
    zoxel_set(world, e, Mouse, mouse_zero);
    zoxel_set(world, e, Raycaster, { { 0, 0 } });
    zoxel_set(world, e, RaycasterTarget, { 0 });
    zoxel_set(world, e, MouseLock, { 0 });
    ecs_defer_end(world);
    prefab_mouse = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab mouse [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_mouse(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_mouse);
    set_unique_entity_name(world, e, "mouse");
    ecs_defer_end(world);
    mouse_entity = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned mouse [%lu].\n", (long int) (e));
    #endif
    return e;
}
ecs_entity_t mouse_prefab;
ecs_entity_t mouse_entity;

ecs_entity_t spawn_prefab_mouse(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "mouse_prefab");
    set_unique_entity_name(world, e, "mouse_prefab");
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab mouse [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Device);
    zoxel_set(world, e, Mouse, mouse_zero);
    zoxel_set(world, e, Raycaster, { { 0, 0 } });
    zoxel_set(world, e, RaycasterTarget, { 0 });
    ecs_defer_end(world);
    mouse_prefab = e;
    return e;
}

ecs_entity_t spawn_mouse(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, mouse_prefab);
    set_unique_entity_name(world, e, "mouse");
    ecs_defer_end(world);
    mouse_entity = e;
    // printf("- mouse spawned [%lu]\n", (long int) e);
    return e;
}
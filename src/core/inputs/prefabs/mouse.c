ecs_entity_t mouse_prefab;
ecs_entity_t mouse_entity;

ecs_entity_t spawn_prefab_mouse(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "mouse_prefab");
    set_unique_entity_name(world, e, "mouse_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab mouse [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Device);
    zoxel_set(world, e, Mouse, { });
    zoxel_set(world, e, Raycaster, { { } });
    zoxel_set(world, e, RaycasterTarget, { 0 });
    mouse_prefab = e;
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_mouse(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, mouse_prefab);
    set_unique_entity_name(world, e, "mouse");
    // printf("- mouse spawned [%lu]\n", (long int) e);
    mouse_entity = e;
    ecs_defer_end(world);
    return e;
}
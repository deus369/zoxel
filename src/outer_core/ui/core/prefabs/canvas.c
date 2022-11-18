ecs_entity_t canvas_prefab;

void spawn_prefab_canvas(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "canvas_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab canvas [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Canvas);
    zoxel_add(world, e, PixelSize);
    canvas_prefab = e;
    ecs_defer_end(world);
}

ecs_entity_t spawn_canvas(ecs_world_t *world, int2 size)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, canvas_prefab);
    ecs_set(world, e, PixelSize, { size });
    ecs_defer_end(world);
    main_canvas = e;
    #ifdef zoxel_debug_spawns
    printf("Spawned canvas [%lu]\n", (long int) e);
    #endif
    return e;
}
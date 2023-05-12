ecs_entity_t canvas_prefab;

ecs_entity_t spawn_prefab_canvas(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "canvas_prefab");
    zoxel_add_tag(e, Canvas);
    zoxel_add(world, e, PixelSize);
    zoxel_add(world, e, Children);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab canvas [%lu]\n", (long int) (e));
    #endif
    canvas_prefab = e;
    return e;
}

ecs_entity_t spawn_canvas(ecs_world_t *world, int2 size) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, canvas_prefab);
    set_unique_entity_name(world, e, "canvas");
    ecs_set(world, e, PixelSize, { size });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned canvas [%lu]\n", (long int) e);
    #endif
    main_canvas = e;
    return e;
}
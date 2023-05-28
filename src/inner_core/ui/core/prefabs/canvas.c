ecs_entity_t canvas_prefab;

ecs_entity_t spawn_prefab_canvas(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_canvas")
    zox_add_tag(e, Canvas)
    zox_add(e, PixelSize)
    zox_add(e, Children)
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab canvas [%lu]\n", (long int) (e));
    #endif
    canvas_prefab = e;
    return e;
}

ecs_entity_t spawn_canvas(ecs_world_t *world, int2 size) {
    ecs_defer_begin(world);
    zox_instance(canvas_prefab)
    zox_name("canvas")
    zox_set_only(e, PixelSize, { size })
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned canvas [%lu]\n", (long int) e);
    #endif
    main_canvas = e;
    return e;
}
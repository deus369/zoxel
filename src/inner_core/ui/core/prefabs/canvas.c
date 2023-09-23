ecs_entity_t prefab_canvas;

ecs_entity_t spawn_prefab_canvas(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_canvas")
    zox_add_tag(e, Canvas)
    zox_set(e, PixelSize, { int2_zero })
    zox_set(e, Children, { 0, NULL })
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab canvas [%lu]\n", (long int) (e));
    #endif
    prefab_canvas = e;
    return e;
}

ecs_entity_t spawn_canvas(ecs_world_t *world, int2 size) {
    zox_instance(prefab_canvas)
    zox_name("canvas")
    zox_set_only(e, PixelSize, { size })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned canvas [%lu]\n", (long int) e);
    #endif
    main_canvas = e;
    return e;
}
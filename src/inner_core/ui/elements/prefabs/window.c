ecs_entity_t window_prefab;

ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_window")
    zox_add_tag(e, Window);
    zox_add_tag(e, FrameTexture);
    zox_set(e, Color, {{ 66, 35, 25, 255 }});
    // zox_set(e, SelectableState, { 0 });
    add_ui_plus_components(world, e);
    zox_add(e, Children);
    ecs_defer_end(world);
    window_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab window [%lu].\n", (long int) (e));
    #endif
    return e;
}

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)
//! \todo in web build, throws error during resize, if window is around
//      Uncaught TypeError: WebGL2RenderingContext.getAttribLocation: Argument 1 is not an object.
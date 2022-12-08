ecs_entity_t window_prefab;
//! \todo in web build, throws error during resize, if window is around
//      Uncaught TypeError: WebGL2RenderingContext.getAttribLocation: Argument 1 is not an object.
ecs_entity_t spawn_prefab_window(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_window");
    #ifdef zoxel_debug_prefabs
    zoxel_log_arg("spawn_prefab window [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Window);
    zoxel_add_tag(world, e, FrameTexture);
    zoxel_set(world, e, SelectableState, { 0 });
    add_ui_plus_components(world, e);
    zoxel_add(world, e, Children);
    window_prefab = e;
    ecs_defer_end(world);
    return e;
}

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)

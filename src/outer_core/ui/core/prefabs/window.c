ecs_entity_t window_prefab;
    
ecs_entity_t spawn_prefab_window(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "window_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab window [%lu].\n", (long int) (e));
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

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label,
    int2 position, int2 pixel_size, float2 anchor)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    float2 position2D = initialize_ui_components(world, e, canvas, position, pixel_size, anchor, 0);
    ecs_defer_end(world);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1);
    // spawn child header
    int font_size = 28;
    int header_margins = 4;
    children->value[0] = spawn_header(world, e, 
        (int2) { 0, - font_size / 2 - header_margins / 2 },
        (int2) { pixel_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f },
        header_label, font_size, header_margins, 1,
        position2D, pixel_size);
    ecs_modified(world, e, Children);
    return e;
}
    // if (!ecs_has(world, window_prefab, Position2D))
    // {
    //     printf("window_prefab [%lu] has no Position2D component.\n", (long int) window_prefab);
    // }

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)


    // #ifdef zoxel_debug_prefabs
    // printf("spawn window [%lu].\n", (long int) (e));
    // #endif
    // if (!ecs_has(world, e, Position2D))
    // {
    //     printf("Window [%lu] has no Position2D component. Cannot spawn.\n", (long int) e);
    //     ecs_delete(world, e);
    //     // ecs_defer_end(world);
    //     return 0;
    // }
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

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label,
    int2 position, int2 pixel_size, float2 anchor, ecs_entity_t canvas)
{
    int font_size = 28;
    int header_margins = 4;
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    set_unique_entity_name(world, e, "window");
    float2 position2D = initialize_ui_components(world, e, canvas, position, pixel_size, anchor, 0,
        ecs_get(world, canvas, PixelSize)->value);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1);
    children.value[0] = spawn_header(world, e, 
        (int2) { 0, - font_size / 2 - header_margins / 2 },
        (int2) { pixel_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f },
        header_label, font_size, header_margins, 1,
        position2D, pixel_size,
        true);
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log_arg("Spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)

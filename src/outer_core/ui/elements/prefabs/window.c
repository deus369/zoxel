ecs_entity_t window_prefab;
    
ecs_entity_t spawn_prefab_window(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_window");
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
    set_unique_entity_name(world, e, "window");
    float2 position2D = initialize_ui_components(world, e, main_canvas, position, pixel_size, anchor, 0);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 4);
    // spawn child header
    int font_size = 28;
    int header_margins = 4;
    children.value[0] = spawn_header(world, e, 
        (int2) { 0, - font_size / 2 - header_margins / 2 },
        (int2) { pixel_size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f },
        header_label, font_size, header_margins, 1,
        position2D, pixel_size);
    
    children.value[1] = spawn_button(world, e,
        (int2) { 0, font_size * 2 },
        (int2) { font_size * 6, font_size },
        (float2) { 0.5f, 0.5f },
        "Play", font_size, 1,
        position2D, pixel_size);
    zoxel_add_tag(world, children.value[1], PlayGameButton);
    children.value[2] = spawn_button(world, e,
        (int2) { 0, 0 },
        (int2) { font_size * 8, font_size },
        (float2) { 0.5f, 0.5f },
        "Options", font_size, 1,
        position2D, pixel_size);
    // zoxel_add_tag(world, children.value[2], OptionsButton);
    children.value[3] = spawn_button(world, e,
        (int2) { 0, - font_size * 2 },
        (int2) { font_size * 6, font_size },
        (float2) { 0.5f, 0.5f },
        "Exit", font_size, 1,
        position2D, pixel_size);
    zoxel_add_tag(world, children.value[3], ExitGameButton);

    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    printf("Spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)

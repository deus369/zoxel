ecs_entity_t window_prefab;

ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_window")
    zox_add_tag(e, Window)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 7 })
    zox_set(e, OutlineThickness, { 3 })
    zox_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    window_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab window [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 position, int2 pixel_size, float2 anchor, ecs_entity_t canvas) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    int font_size = 28;
    int header_margins = 4;
    zox_instance(window_prefab)
    zox_name("window")
    float2 position2D = initialize_ui_components(world, e, canvas, position, pixel_size, anchor, 0, canvas_size);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1)
    children.value[0] = spawn_header(world, e, (int2) { 0, - font_size / 2 - header_margins / 2 }, (int2) { pixel_size.x, font_size + header_margins}, (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, 1, position2D, pixel_size, 1, canvas_size);
    zox_set_only(e, Children, { children.length, children.value })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)
//! \todo in web build, throws error during resize, if window is around
//      Uncaught TypeError: WebGL2RenderingContext.getAttribLocation: Argument 1 is not an object.
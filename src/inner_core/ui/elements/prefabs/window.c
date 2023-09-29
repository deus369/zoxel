ecs_entity_t prefab_window;

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)
//! \todo in web build, throws error during resize, if window is around
//      Uncaught TypeError: WebGL2RenderingContext.getAttribLocation: Argument 1 is not an object.

ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_window")
    zox_add_tag(e, Window)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_prefab_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    prefab_window = e;
    #ifdef zoxel_debug_prefabs
        zox_log("   > spawn_prefab window [%lu]\n", e);
    #endif
    return e;
}

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 pixel_position2D, int2 pixel_size, float2 anchor, ecs_entity_t canvas, unsigned char layer) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    unsigned char header_layer = layer + 1;
    int font_size = 28;
    int header_margins = 16;
    zox_instance(prefab_window)
    zox_name("window")
    float2 real_position2D = initialize_ui_components(world, e, canvas, pixel_position2D, pixel_size, anchor, layer, canvas_size);
    Children *children = ecs_get_mut(world, e, Children);
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_header(world, e, (int2) { 0, - font_size / 2 - header_margins / 2 }, (int2) { pixel_size.x, font_size + header_margins}, (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, header_layer, real_position2D, pixel_size, 1, canvas_size);
    ecs_modified(world, e, Children);
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned window [%lu]\n", e)
    #endif
    return e;
}
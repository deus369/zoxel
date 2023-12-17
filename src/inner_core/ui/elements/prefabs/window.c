ecs_entity_t prefab_window;

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in zox_set)
//! \todo in web build, throws error during resize, if window is around
//      Uncaught TypeError: WebGL2RenderingContext.getAttribLocation: Argument 1 is not an object.

ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_window")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Window)
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_prefab_set(e, Children, { 0, NULL })
    zox_prefab_set(e, ElementFontSize, { 14 })
    prefab_window = e;
#ifdef zoxel_debug_prefabs
    zox_log("   > spawn_prefab window [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 pixel_position, int2 pixel_size, float2 anchor, ecs_entity_t canvas, unsigned char layer) {
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    unsigned char header_layer = layer + 1;
    int font_size = 28;
    int header_margins = 16;
    zox_instance(prefab_window)
    zox_name("window")
    ecs_entity_t parent = canvas;
    int2 pixel_position_global = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, pixel_position_global);
    Children *children = ecs_get_mut(world, e, Children);
    resize_memory_component(Children, children, ecs_entity_t, 1)
    children->value[0] = spawn_header(world, e, canvas, (int2) { 0, - font_size / 2 - header_margins / 2 }, (int2) { pixel_size.x, font_size + header_margins}, (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, header_layer, pixel_position_global, pixel_size, 1, canvas_size);
    zox_modified(e, Children)
#ifdef zoxel_debug_spawns
    zox_log(" > spawned window [%lu]\n", e)
#endif
    return e;
}

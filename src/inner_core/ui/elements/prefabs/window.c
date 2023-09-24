extern ecs_entity_t spawn_ui_line2D(ecs_world_t *world, ecs_entity_t canvas, int2 point_a, int2 point_b, color line_color, float thickness, double life_time, float2 parent_real_position, int2 parent_position, unsigned char layer);
ecs_entity_t prefab_window;

ecs_entity_t spawn_prefab_window(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_prefab_name("prefab_window")
    zox_add_tag(e, Window)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 7 })
    zox_set(e, OutlineThickness, { 3 })
    zox_set(e, Color, {{ 66, 35, 25, 255 }})
    zox_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    prefab_window = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab window [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 pixel_position2D, int2 pixel_size, float2 anchor, ecs_entity_t canvas, unsigned char layer) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    unsigned char header_layer = layer + 1;
    // unsigned char lines_layer = layer + 2;
    int font_size = 28;
    int header_margins = 16;
    zox_instance(prefab_window)
    zox_name("window")
    float2 real_position2D = initialize_ui_components(world, e, canvas, pixel_position2D, pixel_size, anchor, layer, canvas_size);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1)
    children->value[0] = spawn_header(world, e, (int2) { 0, - font_size / 2 - header_margins / 2 }, (int2) { pixel_size.x, font_size + header_margins}, (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, header_layer, real_position2D, pixel_size, 1, canvas_size);
    //color edge_color = (color) { 33, 155, 155, 155 };
    //int edge_size = 4;
    /*
    children.value[1] = spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { pixel_size.x, 0 }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[2] = spawn_ui_line2D(world, main_canvas, (int2) { pixel_size.x, 0 }, (int2) { pixel_size.x, pixel_size.y }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[3] = spawn_ui_line2D(world, main_canvas, (int2) { pixel_size.x, pixel_size.y }, (int2) { 0, pixel_size.y }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[4] = spawn_ui_line2D(world, main_canvas, (int2) { 0, pixel_size.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    */
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, cross_color, 4.0f, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 1080 }, (int2) { 1920, 0 }, cross_color, 4.0f, 0.0);
    ecs_modified(world, e, Children);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}

// i'm getting prefab issues with a override component not appearing on the spawned entity, wondering if anyone else is geting this
// (im thinking its something to do with deffered operations in ecs_set)
//! \todo in web build, throws error during resize, if window is around
//      Uncaught TypeError: WebGL2RenderingContext.getAttribLocation: Argument 1 is not an object.
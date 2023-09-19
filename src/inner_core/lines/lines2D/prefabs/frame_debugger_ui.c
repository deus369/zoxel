ecs_entity_t prefab_frame_debugger_ui;
ecs_entity_t frame_debugger_ui;

ecs_entity_t spawn_prefab_frame_debugger_ui(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_window)
    zox_name("prefab_frame_debugger_ui")
    // zox_add_tag(e, MainMenu)
    ecs_defer_end(world);
    prefab_frame_debugger_ui = e;
    return e;
}

ecs_entity_t spawn_frame_debugger_ui(ecs_world_t *world, const char *header_label, int2 pixel_position2D, int2 pixel_size, float2 anchor, ecs_entity_t canvas, unsigned char layer) {
    int2 canvas_size = ecs_get(world, main_canvas, PixelSize)->value;
    // const unsigned char layer = 2;
    int lines_count = 60; // 30;
    float lines_thickness = 4;
    int line_margins = 16;
    float line_spacing = ( pixel_size.x - line_margins * 2 ) / (float) (lines_count - 1);
    zoxel_log(" > line_spacing [%f] - size [%i]\n", line_spacing, pixel_size.x);
    unsigned char header_layer = layer + 1;
    unsigned char lines_layer = layer + 2;
    int font_size = 28;
    int header_margins = 16;
    color line_color = (color) { 60, 22, 22, 155 };
    zox_instance(prefab_frame_debugger_ui)
    zox_name("frame_debugger_ui")
    float2 real_position2D = initialize_ui_components(world, e, canvas, pixel_position2D, pixel_size, anchor, layer, canvas_size);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1 + lines_count)
    children.value[0] = spawn_header(world, e, (int2) { 0, - font_size / 2 - header_margins / 2 }, (int2) { pixel_size.x, font_size + header_margins}, (float2) { 0.5f, 1.0f }, header_label, font_size, header_margins, header_layer, real_position2D, pixel_size, 1, canvas_size);
    color edge_color = (color) { 33, 155, 155, 155 };
    int edge_size = 4;
    int lines_min_height = font_size;
    int lines_max_height = pixel_size.y - (font_size + header_margins) - font_size;
    for (int i = 0; i < lines_count; i++) {
        int position_x = line_margins + i * line_spacing;
        children.value[1 + i] = spawn_ui_line2D(world, main_canvas, (int2) { position_x, lines_min_height }, (int2) { position_x, lines_max_height }, line_color, lines_thickness, 0.0, real_position2D, pixel_position2D, lines_layer);
        zox_add_tag(children.value[1 + i], FrameDebugLine)
        zox_set(children.value[1 + i], ChildIndex, { i })
    }
    zox_set_only(e, Children, { children.length, children.value })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}

ecs_entity_t zoxel_window;

void spawn_zoxel_window(ecs_world_t *world) {
    if (zoxel_window != 0 && ecs_is_alive(world, zoxel_window)) {
        zoxel_log("Hiding zoxel window.\n");
        zox_delete(zoxel_window)
        zoxel_window = 0;
        return;
    }
    zoxel_log("Showing zoxel window.\n");
    const unsigned char layer = 3;
    int2 test_window_size = { 380, 480 };
    int2 test_window_position = { - test_window_size.x / 2, test_window_size.y / 2 };
    float2 test_window_anchor = { 1.0f, 0.0f };
    zoxel_window = spawn_frame_debugger_ui(world, "debugger", test_window_position, test_window_size, test_window_anchor, main_canvas, layer);
}

/*children.value[1] = spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { pixel_size.x, 0 }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[2] = spawn_ui_line2D(world, main_canvas, (int2) { pixel_size.x, 0 }, (int2) { pixel_size.x, pixel_size.y }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[3] = spawn_ui_line2D(world, main_canvas, (int2) { pixel_size.x, pixel_size.y }, (int2) { 0, pixel_size.y }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[4] = spawn_ui_line2D(world, main_canvas, (int2) { 0, pixel_size.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);*/
    
ecs_entity_t prefab_frame_debugger_ui;
ecs_entity_t frame_debugger_ui;

ecs_entity_t spawn_prefab_frame_debugger_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_frame_debugger_ui")
    prefab_frame_debugger_ui = e;
    return e;
}

ecs_entity_t spawn_frame_debugger_ui(ecs_world_t *world, const char *header_label, int2 pixel_position2D, int2 pixel_size, float2 anchor, ecs_entity_t canvas, unsigned char layer) {
    unsigned char is_close_button = 1;
    int2 canvas_size = zox_get_value(canvas, PixelSize)
    color line_color = (color) { 6, 222, 222, 255 };
    int lines_count = record_frames_count; // 60;
    unsigned char header_layer = layer + 1;
    unsigned char lines_layer = layer + 2;
    int font_size = 28;
    int header_margins = 16;
    float lines_thickness = 1.0f;
    int line_margins = 8;   // x
    float line_spacing = ( pixel_size.x - line_margins * 2 ) / (float) (lines_count - 1);
    int lines_min_height = 4;
    int lines_max_height = pixel_size.y - (font_size + header_margins) - font_size;
    // zoxel_log(" > line_spacing [%f] - size [%i]\n", line_spacing, pixel_size.x);
    zox_instance(prefab_frame_debugger_ui)
    zox_name("frame_debugger_ui")
    float2 real_position2D = initialize_ui_components(world, e, canvas, pixel_position2D, pixel_size, anchor, layer, canvas_size);
    int2 pixel_position_global = int2_zero;
    int children_count = 1 + lines_count;
    Children *children = ecs_get_mut(world, e, Children);
    resize_memory_component(Children, children, ecs_entity_t, children_count)
    int2 header_position = (int2) { 0, - font_size / 2 - header_margins / 2 };
    int2 header_size = (int2) { pixel_size.x, font_size + header_margins };
    float2 header_anchor = (float2) { 0.5f, 1.0f };
    children->value[0] = spawn_header(world, e, canvas, header_position, header_size, header_anchor, header_label, font_size, header_margins, header_layer, pixel_position_global, pixel_size, is_close_button, canvas_size);
    for (int i = 0; i < lines_count; i++) {
        int position_x = line_margins + i * line_spacing;
        int2 start_position = (int2) { position_x, lines_min_height };
        int2 end_position = (int2) { position_x, lines_max_height };
        ecs_entity_t line = spawn_ui_line2D(world, main_canvas, start_position, end_position, line_color, lines_thickness, 0, real_position2D, pixel_position2D, lines_layer);
        zox_set(line, ChildIndex, { i })
        zox_add_tag(line, FrameDebugLine)
        children->value[1 + i] = line;
    }
    ecs_modified(world, e, Children);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned window [%lu]\n", (long int) e);
    #endif
    return e;
}

ecs_entity_t zoxel_window;

void spawn_zoxel_window(ecs_world_t *world) {
    if (zoxel_window != 0 && ecs_is_alive(world, zoxel_window)) {
        zoxel_log(" > hiding frame debugger\n");
        zox_delete(zoxel_window)
        zoxel_window = 0;
        return;
    }
    zoxel_log(" > showing frame debugger\n");
    const unsigned char layer = 3;
    int2 test_window_size = { 380, 380 };
    int2 test_window_position = { - test_window_size.x / 2, test_window_size.y / 2 };
    float2 test_window_anchor = { 1.0f, 0.0f };
    zoxel_window = spawn_frame_debugger_ui(world, "debugger", test_window_position, test_window_size, test_window_anchor, main_canvas, layer);
}

/*children.value[1] = spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { pixel_size.x, 0 }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[2] = spawn_ui_line2D(world, main_canvas, (int2) { pixel_size.x, 0 }, (int2) { pixel_size.x, pixel_size.y }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[3] = spawn_ui_line2D(world, main_canvas, (int2) { pixel_size.x, pixel_size.y }, (int2) { 0, pixel_size.y }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);
    children.value[4] = spawn_ui_line2D(world, main_canvas, (int2) { 0, pixel_size.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0, real_position2D, pixel_position2D, lines_layer);*/
    

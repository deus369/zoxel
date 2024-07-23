ecs_entity_t spawn_prefab_frame_debugger_ui(ecs_world_t *world) {
    zox_prefab_child(prefab_window)
    zox_prefab_name("prefab_frame_debugger_ui")
    zox_add_tag(e, FrameDebuggerWindow)
    zox_prefab_add(e, PlotDataDouble)
    zox_get_muter(e, PlotDataDouble, data)
    resize_memory_component(PlotDataDouble, data, double, record_frames_count)
    for (int i = 0; i < record_frames_count; i++) data->value[i] = 0;
    prefab_frame_debugger_ui = e;
    return e;
}

ecs_entity_t spawn_frame_debugger_ui(ecs_world_t *world, const ecs_entity_t prefab, const char *header_label, const int2 pixel_position, const int2 pixel_size, const float2 anchor, const ecs_entity_t canvas, const unsigned char layer) {
    // defaultt header data
    const unsigned char header_layer = layer + 1;
    const int font_size = 28;
    const int header_margins = 16;
    const float2 header_anchor = (float2) { 0.5f, 1.0f };
    const int2 header_position = (int2) { 0, - font_size / 2 - header_margins / 2 };
    const int2 header_size = (int2) { pixel_size.x, font_size + header_margins };

    const unsigned char is_header = 1;
    const unsigned char is_plot_sub_label = 1;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const unsigned char is_close_button = 1;
    const color line_color = (color) { 6, 222, 222, 255 };
    const int lines_count = record_frames_count;
    const unsigned char lines_layer = layer + 2;
    const float lines_thickness = 1.0f;
    const int line_margins = 8;   // x
    const float line_spacing = ( pixel_size.x - line_margins * 2 ) / (float) (lines_count - 1);
    const int lines_min_height = 4;
    const int lines_max_height = pixel_size.y - (font_size + header_margins) - font_size;
    const ecs_entity_t parent = canvas;
    const int2 canvas_position = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, pixel_position, anchor);
    const float2 position2D = get_element_position(canvas_position, canvas_size);
    const int children_count = is_header + is_plot_sub_label + lines_count;
    // zoxel_log(" > line_spacing [%f] - size [%i]\n", line_spacing, pixel_size.x);
    zox_instance(prefab)
    zox_name("frame_debugger_ui")
    // zox_set(e, HeaderHeight, { header_size.y })
    initialize_element(world, e, parent, canvas, pixel_position, pixel_size, pixel_size, anchor, layer, position2D, canvas_position);
    set_window_bounds_to_canvas(world, e, canvas_size, pixel_size, anchor);
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, children_count)
    if (is_header) {
        children->value[0] = spawn_header(world, e, canvas, header_position, header_size, header_anchor, header_label, font_size, header_margins, header_layer, canvas_position, pixel_size, is_close_button, canvas_size);
    }
    if (is_plot_sub_label) {
        SpawnZext zextSpawnData = {
            .canvas = {
                .e = canvas,
                .size = canvas_size
            },
            .parent = {
                .e = e,
                .position = pixel_position,
                .size = pixel_size
            },
            .element = {
                .prefab = prefab_zext,
                .position = (int2) { 0, -(header_size.y) },
                .layer = header_layer,
                .anchor = (float2) { 0, 1.0f },
            },
            .zext = {
                .text = "min 5.4\nmax 24.3",
                .font_size = 12,
                .font_thickness = 1,
                .alignment = zox_mesh_alignment_top_left,
                .padding = (byte2) { 16, 4 },
                .font_fill_color = default_font_fill_color,
                .font_outline_color = default_font_outline_color
            }
        };
        const ecs_entity_t e2 = spawn_zext(world, &zextSpawnData);
        children->value[is_header] = e2;
        zox_add_tag(e2, PlotLabel)
    }
    for (int i = 0; i < lines_count; i++) {
        const int position_x = line_margins + i * line_spacing;
        const int2 start_position = (int2) { position_x, lines_min_height };
        const int2 end_position = (int2) { position_x, lines_max_height };
        const ecs_entity_t e2 = spawn_ui_line2D_v2(world, canvas, e, start_position, end_position, line_color, lines_thickness, 0, position2D, pixel_position, lines_layer);
        zox_set(e2, ChildIndex, { i })
        zox_set(e2, ParentLink, { e })
        zox_add_tag(e2, PlotLine)
        children->value[is_header + is_plot_sub_label + i] = e2;
    }
    zox_modified(e, Children)
    plot_window_time = e;
    return e;
}

ecs_entity_t spawn_frame_debugger(ecs_world_t *world, const ecs_entity_t canvas) {
    const unsigned char layer = 3;
    const int2 test_window_size = { 380, 380 };
    const int2 test_window_position = { - test_window_size.x / 2, test_window_size.y / 2 };
    const float2 test_window_anchor = { 1.0f, 0.0f };
    // zox_log(" > showing frame_debugger_window\n")
    return spawn_frame_debugger_ui(world, prefab_frame_debugger_ui, "debugger", test_window_position, test_window_size, test_window_anchor, canvas, layer);
}

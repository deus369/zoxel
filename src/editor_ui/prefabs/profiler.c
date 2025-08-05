ecs_entity_t spawn_frame_debugger_ui(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const char *header_label,
    const int2 position,
    const int2 size,
    const float2 anchor,
    const ecs_entity_t canvas,
    const byte layer)
{
    const byte plots_count = 2;
    const color plot_colors[] = {
        (color) { 33, 133, 133, 255 },
        (color) { 133, 133, 133, 255 },
    };

    const byte plot_layer = layer + 1;
    const byte header_layer = layer + 3;
    // const byte lines_layer = layer + 2;

    const int font_size = 28;
    const int header_margins = 16;
    const float2 header_anchor = (float2) { 0.5f, 1.0f };
    const int2 header_position = (int2) { 0, - font_size / 2 - header_margins / 2 };
    const int2 header_size = (int2) { size.x, font_size + header_margins };

    const byte is_header = 1;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const byte is_close_button = 1;

    const ecs_entity_t parent = canvas;
    const int2 canvas_position = get_element_pixel_position_global(int2_half(canvas_size), canvas_size, position, anchor);
    const float2 positionf = get_element_position(canvas_position, canvas_size);

    const int children_count = is_header + plots_count;

    // zox_log(" > line_spacing [%f] - size [%i]\n", line_spacing, pixel_size.x);
    zox_instance(prefab)
    zox_name("frame_debugger_ui")
    zox_add_tag(e, FrameDebuggerWindow)
    initialize_element(world,
        e,
        parent,
        canvas,
        position,
        size,
        size,
        anchor,
        layer,
        positionf,
        canvas_position);
    set_window_bounds_to_canvas(world, e, canvas_size, size, anchor);

    Children children = (Children) { };
    initialize_Children(&children, children_count);

    if (is_header) {
        children.value[0] = spawn_header(world,
            e,
            canvas,
            header_position,
            header_size,
            header_anchor,
            header_label,
            font_size,
            header_margins,
            header_layer,
            canvas_position,
            size,
            is_close_button,
            canvas_size);
    }
    int2 plot_size = size;
    plot_size.y -= header_size.y;
    for (int i = 0; i < plots_count; i++) {
        children.value[is_header + i] = spawn_plot_graph(world,
            canvas,
            e,
            position,
            size,
            prefab_layout2 + i,
            plot_layer,
            plot_size,
            record_frames_count,
            0,
            plot_colors[i],
            1,
            i * 2);
    }
    // todo: seperate plot data from the graphs here
        // - hotkey to switch them
        // PlotLinks from our Profiler
    plot_time = children.value[1];
    plot_time_system = children.value[2];

    zox_set_ptr(e, Children, children);
    return e;
}

ecs_entity_t spawn_frame_debugger(ecs_world_t *world, const ecs_entity_t canvas) {
    const byte layer = game_overlay_layer + 3; // 3;
    const int2 test_window_size = { 380, 380 };
    const int2 test_window_position = { - test_window_size.x / 2, test_window_size.y / 2 };
    const float2 test_window_anchor = { 1.0f, 0.0f };
    // zox_log(" > showing frame_debugger_window\n")
    return spawn_frame_debugger_ui(world,
        prefab_frame_debugger_ui,
        "debugger",
        test_window_position,
        test_window_size,
        test_window_anchor,
        canvas,
        layer);
}

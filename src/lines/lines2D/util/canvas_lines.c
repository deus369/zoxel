void spawn_canvas_edge_lines(ecs_world_t *world, const ecs_entity_t canvas, const int edge_size, const color edge_color) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const byte lines_layer = max_layers2D - 2;
    // const int min_dim = int2_min(canvas_size);
    // const int edge_size = min_dim / 80;
    // const color edge_color = (color) { 13, 44, 13, 255 };
    const float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    const float2 offset = (float2) { - aspect_ratio / 2.0f, - 1 / 2.0f };
    spawn_ui_line2D(world, canvas, canvas, int2_zero, int2_zero, float2_zero, (float2) { 1, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, canvas, int2_zero, int2_zero, float2_zero, (float2) { 0, 1 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, canvas, int2_zero, int2_zero, (float2) { 1, 1 }, (float2) { 1, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, canvas, int2_zero, int2_zero, (float2) { 1, 1 }, (float2) { 0, 1 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
}

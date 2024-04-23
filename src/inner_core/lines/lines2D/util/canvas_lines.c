void spawn_canvas_edge_lines(ecs_world_t *world, ecs_entity_t canvas) {
    int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
    const unsigned char lines_layer = 8;
    int min_dim = int2_min(canvas_size);
    int edge_size = min_dim / 80;
    // const int edge_size = 32;
    // const color edge_color = (color) { 99, 13, 13, 255 };
    const color edge_color = (color) { 13, 44, 13, 255 };
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    // test ui line
    // color edge_color = (color) { 8, 3, 3, 255 };
    // color cross_color =  (color) { 55, 33, 12, 255 };
    float2 offset = (float2) { - aspect_ratio / 2.0f, - 1 / 2.0f };
    /*spawn_ui_line2D(world, canvas, (int2) { 0, 0 }, (int2) { screen_dimensions.x, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, (int2) { screen_dimensions.x, 0 }, (int2) { screen_dimensions.x, screen_dimensions.y }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, (int2) { screen_dimensions.x, screen_dimensions.y }, (int2) { 0, screen_dimensions.y }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, (int2) { 0, screen_dimensions.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);*/


    spawn_ui_line2D(world, canvas, int2_zero, int2_zero, float2_zero, (float2) { 1, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, int2_zero, int2_zero, float2_zero, (float2) { 0, 1 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, int2_zero, int2_zero, (float2) { 1, 1 }, (float2) { 1, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, int2_zero, int2_zero, (float2) { 1, 1 }, (float2) { 0, 1 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);

    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, cross_color, 4.0f, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 1080 }, (int2) { 1920, 0 }, cross_color, 4.0f, 0.0);
}

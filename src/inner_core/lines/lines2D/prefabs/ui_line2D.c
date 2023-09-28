ecs_entity_t prefab_ui_line2D;
extern ecs_entity_t prefab_temporary_ui_line2D;
extern void set_ui_line_position(LineData2D *lineData2D, int4 linePosition2D, float2 canvas_size_f, float aspect_ratio);

ecs_entity_t spawn_prefab_ui_line2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_ui_line2D")
    zox_add_tag(e, Line2D);
    zox_set(e, LineData2D, { float4_zero })
    zox_set(e, LineLocalPosition2D, { int4_zero })
    zox_set(e, LinePosition2D, { int4_zero })
    zox_set(e, LineThickness, { 1 })
    zox_set(e, CanvasLink, { })
    zox_set(e, Layer2D, { 0 })    // use to render in order during ui render process
    zox_set(e, Color, { { 255, 0, 0, 255 } })
    zox_set(e, ChildIndex, { 0 })
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab ui_line2D [%lu].\n", (long int) (e));
    #endif
    prefab_ui_line2D = e;
    return e;
}


ecs_entity_t spawn_ui_line2D(ecs_world_t *world, ecs_entity_t canvas, int2 point_a, int2 point_b, color line_color, float thickness, double life_time, float2 parent_real_position, int2 parent_position, unsigned char layer) {
    ecs_entity_t e;
    if (life_time == 0.0) e = ecs_new_w_pair(world, EcsIsA, prefab_ui_line2D);
    else e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_ui_line2D);
    // set_unique_entity_name(world, e, "line2D");
    int2 canvas_size = screen_dimensions;
    if (canvas != 0) {
        canvas_size = ecs_get(world, canvas, PixelSize)->value;
        zox_set_only(e, CanvasLink, { canvas })
    }
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    // parent_real_position.x -= aspect_ratio / 2.0f;
    // parent_real_position.y -= 1 / 2.0f;
    int4 local_line_position2D = (int4) { point_a.x, point_a.y, point_b.x, point_b.y };
    int4 line_position2D = get_new_line_position(parent_real_position, canvas_size_f, aspect_ratio, parent_position, local_line_position2D);
    // const LinePosition2D linePosition2D = (LinePosition2D) { line_position2D };
    // zoxel_log(" > line [%ix%ix%ix%i]\n", line_position2D.x, line_position2D.y, line_position2D.z, line_position2D.w);
    //  { point_a.x, point_a.y, point_b.x, point_b.y } };
    zox_set_only(e, Layer2D, { layer })
    zox_set_only(e, Color, { line_color })
    zox_set_only(e, LineThickness, { thickness })
    zox_set_only(e, LineLocalPosition2D, { local_line_position2D })
    zox_set_only(e, LinePosition2D, { line_position2D })
    // zox_set_only(e, LinePosition2D, { { point_a.x, point_a.y, point_b.x, point_b.y } })
    // PixelPosition would be... ?
    //LineData2D lineData2D = (LineData2D) { float4_zero };
    LineData2D *lineData2D = ecs_get_mut(world, e, LineData2D);
    set_ui_line_position(lineData2D, line_position2D, canvas_size_f, aspect_ratio);
    ecs_modified(world, e, LineData2D);
    // zox_set_only(e, LineData2D, { lineData2D.value })
    if (life_time != 0.0f) zox_set_only(e, DestroyInTime, { life_time })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned ui_line2D [%lu]\n", (long int) e);
    #endif
    return e;
}

void spawn_canvas_edge_lines(ecs_world_t *world, ecs_entity_t canvas) {
    const unsigned char lines_layer = 8;
    const int edge_size = 32;
    const color edge_color = (color) { 99, 13, 13, 255 };
    int2 canvas_size = ecs_get(world, canvas, PixelSize)->value;
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    // test ui line
    // color edge_color = (color) { 8, 3, 3, 255 };
    // color cross_color =  (color) { 55, 33, 12, 255 };
    float2 offset = (float2) { - aspect_ratio / 2.0f, - 1 / 2.0f };
    spawn_ui_line2D(world, canvas, (int2) { 0, 0 }, (int2) { screen_dimensions.x, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, (int2) { screen_dimensions.x, 0 }, (int2) { screen_dimensions.x, screen_dimensions.y }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, (int2) { screen_dimensions.x, screen_dimensions.y }, (int2) { 0, screen_dimensions.y }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    spawn_ui_line2D(world, canvas, (int2) { 0, screen_dimensions.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0, offset, int2_zero, lines_layer);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, cross_color, 4.0f, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 1080 }, (int2) { 1920, 0 }, cross_color, 4.0f, 0.0);
}
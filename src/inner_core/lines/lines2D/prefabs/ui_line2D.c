ecs_entity_t prefab_ui_line2D;
extern ecs_entity_t prefab_temporary_ui_line2D;
extern void set_ui_line_position(LineData2D *lineData2D, const LineElementData *lineElementData, float2 canvas_size_f, float aspect_ratio);

ecs_entity_t spawn_prefab_ui_line2D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_ui_line2D")
    zox_add_tag(e, Line2D);
    zox_set(e, LineData2D, { { 0, 0, 0, 0 } })
    zox_set(e, LineElementData, { { 0, 0, 0, 0 } })
    zox_set(e, LineThickness, { 1 })
    zox_set(e, CanvasLink, { })
    zox_set(e, Layer2D, { 0 })    // use to render in order during ui render process
    zox_set(e, Color, { { 255, 0, 0, 255 } })
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab ui_line2D [%lu].\n", (long int) (e));
    #endif
    prefab_ui_line2D = e;
    return e;
}


ecs_entity_t spawn_ui_line2D(ecs_world_t *world, ecs_entity_t canvas, int2 point_a, int2 point_b, color line_color, float thickness, double life_time) {
    ecs_entity_t e;
    if (life_time == 0.0) e = ecs_new_w_pair(world, EcsIsA, prefab_ui_line2D);
    else e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_ui_line2D);
    // set_unique_entity_name(world, e, "line2D");
    int2 canvas_size = screen_dimensions;
    if (canvas != 0) {
        canvas_size = ecs_get(world, canvas, PixelSize)->value;
        ecs_set(world, e, CanvasLink, { canvas });
    }
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    const LineElementData lineElementData = (LineElementData) { { point_a.x, point_a.y, point_b.x, point_b.y } };
    LineData2D lineData2D;
    set_ui_line_position(&lineData2D, &lineElementData, canvas_size_f, aspect_ratio);
    zox_set_only(e, Color, { line_color })
    zox_set_only(e, LineThickness, { thickness })
    zox_set_only(e, LineElementData, { { point_a.x, point_a.y, point_b.x, point_b.y } })
    zox_set_only(e, LineData2D, { lineData2D.value })
    if (life_time != 0.0f) zox_set_only(e, DestroyInTime, { life_time })
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned ui_line2D [%lu]\n", (long int) e);
    #endif
    return e;
}

void spawn_canvas_edge_lines(ecs_world_t *world, ecs_entity_t main_canvas) {
    // test ui line
    // color edge_color = (color) { 8, 3, 3, 255 };
    // color cross_color =  (color) { 55, 33, 12, 255 };
    color edge_color = (color) { 66, 3, 3, 255 };
    int edge_size = canvas_edge_size;
    spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { screen_dimensions.x, 0 }, edge_color, edge_size, 0.0);
    spawn_ui_line2D(world, main_canvas, (int2) { screen_dimensions.x, 0 }, (int2) { screen_dimensions.x, screen_dimensions.y }, edge_color, edge_size, 0.0);
    spawn_ui_line2D(world, main_canvas, (int2) { screen_dimensions.x, screen_dimensions.y }, (int2) { 0, screen_dimensions.y }, edge_color, edge_size, 0.0);
    spawn_ui_line2D(world, main_canvas, (int2) { 0, screen_dimensions.y }, (int2) { 0, 0 }, edge_color, edge_size, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 0 }, (int2) { 1920, 1080 }, cross_color, 4.0f, 0.0);
    // spawn_ui_line2D(world, main_canvas, (int2) { 0, 1080 }, (int2) { 1920, 0 }, cross_color, 4.0f, 0.0);
}
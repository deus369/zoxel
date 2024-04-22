float2 get_ui_real_position2D_canvas_no_anchor(int2 local_pixel_position, float2 canvas_size_f, float aspect_ratio) {
    return (float2) { 
            (2.0f * (local_pixel_position.x  / canvas_size_f.x) - 1.0f), // aspect_ratio,
            (2.0f * (local_pixel_position.y  / canvas_size_f.y) - 1.0f) };
}

void set_ui_line_position(LineData2D *lineData2D, int4 linePosition2D, float2 canvas_size_f, float aspect_ratio) {
    float2 point_a = get_ui_real_position2D_canvas_no_anchor(
        (int2) { linePosition2D.x, linePosition2D.y }, canvas_size_f, aspect_ratio);
    float2 point_b = get_ui_real_position2D_canvas_no_anchor(
        (int2) { linePosition2D.z, linePosition2D.w }, canvas_size_f, aspect_ratio);
    lineData2D->value = (float4) { point_a.x, point_a.y, point_b.x, point_b.y };
    // printf("Position3D of line set to: %fx%fx%fx%f from %ix%ix%ix%i\n",
    //    point_a.x, point_a.y, point_b.x, point_b.y,
    //    linePosition2D->value.x, linePosition2D->value.y, linePosition2D->value.z, linePosition2D->value.w);
    // lineData2D->value = (float4) { -1.0f, 0, 1.0f, 0 };
}

void Line2DElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    const LinePosition2D *lineElementDatas = ecs_field(it, LinePosition2D, 2);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    LineData2D *lineData2Ds = ecs_field(it, LineData2D, 4);
    for (int i = 0; i < it->count; i++) {
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (!zox_valid(canvasLink->value)) continue;
        int2 canvas_size = ecs_get(world, canvasLink->value, PixelSize)->value;
        float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
        float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
        const LinePosition2D *linePosition2D = &lineElementDatas[i];
        LineData2D *lineData2D = &lineData2Ds[i];
        // set render position based on canvas
        set_ui_line_position(lineData2D, linePosition2D->value, canvas_size_f, aspect_ratio);
    }
    // zoxel_log(" > lines updated\n");
} zox_declare_system(Line2DElementSystem)

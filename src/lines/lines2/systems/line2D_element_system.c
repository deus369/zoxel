float2 get_ui_real_position2D_canvas_no_anchor(const int2 local_pixel_position, const float2 canvas_size_f, const float aspect_ratio) {
    return (float2) { (2.0f * (local_pixel_position.x  / canvas_size_f.x) - 1.0f), // aspect_ratio,
            (2.0f * (local_pixel_position.y  / canvas_size_f.y) - 1.0f) };
}

void set_ui_line_position(LineData2D *lineData2D, const int4 linePosition2D, const float2 canvas_size_f, const float aspect_ratio) {
    const float2 point_a = get_ui_real_position2D_canvas_no_anchor(
        (int2) { linePosition2D.x, linePosition2D.y }, canvas_size_f, aspect_ratio);
    const float2 point_b = get_ui_real_position2D_canvas_no_anchor(
        (int2) { linePosition2D.z, linePosition2D.w }, canvas_size_f, aspect_ratio);
    lineData2D->value = (float4) { point_a.x, point_a.y, point_b.x, point_b.y };
}

// this just sets posiions - sets render position based on canvas
void Line2DElementSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(LinePosition2D)
    zox_sys_in(CanvasLink)
    zox_sys_out(LineData2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_i(LinePosition2D, linePosition2D)
        zox_sys_o(LineData2D, lineData2D)
        if (!zox_valid(canvasLink->value)) {
            continue;
        }
        const int2 canvas_size = zox_get_value(canvasLink->value, PixelSize)
        const float2 canvas_size_f = int2_to_float2(canvas_size);
        const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
        set_ui_line_position(lineData2D, linePosition2D->value, canvas_size_f, aspect_ratio);
    }
} zox_declare_system(Line2DElementSystem)
ecs_entity_t prefab_ui_line2D;
extern ecs_entity_t prefab_temporary_ui_line2D;
extern void set_ui_line_position(LineData2D *lineData2D, int4 linePosition2D, float2 canvas_size_f, float aspect_ratio);

ecs_entity_t spawn_prefab_ui_line2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_ui_line2D")
    zox_add_tag(e, Line2D)
    zox_add_tag(e, ElementLine2D)
    zox_prefab_set(e, LineData2D, { float4_zero })
    zox_prefab_set(e, LineLocalPosition2D, { int4_zero })
    zox_prefab_set(e, LinePosition2D, { int4_zero })
    zox_prefab_set(e, LineAnchor, { float4_zero })
    zox_prefab_set(e, LineThickness, { 1 })
    zox_prefab_set(e, CanvasLink, { 0 })
    zox_prefab_set(e, Layer2D, { 0 })    // use to render in order during ui render process
    zox_prefab_set(e, Color, { { 255, 0, 0, 255 } })
    zox_prefab_set(e, ChildIndex, { 0 })
    prefab_ui_line2D = e;
    return e;
}

void offset_line_points(int4 *points, const float4 line_anchor, const float2 canvas_size_f) {
    points->x += canvas_size_f.x * line_anchor.x;
    points->y += canvas_size_f.y * line_anchor.y;
    points->z += canvas_size_f.x * line_anchor.z;
    points->w += canvas_size_f.y * line_anchor.w;
}

void resize_ui_line2D(ecs_world_t *world, ecs_entity_t e, int2 canvas_size) {
    if (!zox_has(e, LineLocalPosition2D)) return;
    const float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    const float4 line_anchor = zox_get_value(e, LineAnchor)
    int4 points = zox_get_value(e, LineLocalPosition2D)
    offset_line_points(&points, line_anchor, canvas_size_f);
    // todo: fix this, these are parent - canvas atm
    const float2 parent_real_position = (float2) { - aspect_ratio / 2.0f, - 1 / 2.0f };
    const int2 parent_position = int2_zero;
    const int4 line_position2D = get_new_line_position(parent_real_position, canvas_size_f, aspect_ratio, parent_position, points);
    zox_set(e, LinePosition2D, { line_position2D })
    LineData2D *lineData2D = zox_get_mut(e, LineData2D)
    set_ui_line_position(lineData2D, line_position2D, canvas_size_f, aspect_ratio);
    zox_modified(e, LineData2D)
}

ecs_entity_t spawn_ui_line2D(ecs_world_t *world, ecs_entity_t canvas, const ecs_entity_t parent, int2 point_a, const int2 point_b, const float2 anchor_a, const float2 anchor_b, const color line_color, const float thickness, const double life_time, const float2 parent_real_position, const int2 parent_position, const byte layer) {
    if (canvas == 0) canvas = zox_canvases[0];
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    ecs_entity_t e;
    if (life_time == 0.0) {
        e = zox_instancee(prefab_ui_line2D)
    } else {
        e = zox_instancee(prefab_temporary_ui_line2D)
    }
    zox_name("ui_line2D")
    zox_set(e, CanvasLink, { canvas })
    const float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    const float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    const float4 line_anchor = (float4) { anchor_a.x, anchor_a.y, anchor_b.x, anchor_b.y };
    int4 points = (int4) { point_a.x, point_a.y, point_b.x, point_b.y };
    zox_set(e, LineLocalPosition2D, { points })
    offset_line_points(&points, line_anchor, canvas_size_f);
    int4 line_position2D = get_new_line_position(parent_real_position, canvas_size_f, aspect_ratio, parent_position, points);
    zox_set(e, Layer2D, { layer })
    zox_set(e, Color, { line_color })
    zox_set(e, LineThickness, { thickness })
    zox_set(e, LinePosition2D, { line_position2D })
    zox_set(e, LineAnchor, { line_anchor })
    LineData2D *lineData2D = zox_get_mut(e, LineData2D)
    set_ui_line_position(lineData2D, line_position2D, canvas_size_f, aspect_ratio);
    zox_modified(e, LineData2D)
    if (life_time != 0.0f) zox_set(e, DestroyInTime, { life_time })
    // adds to canvas
    if (parent == canvas) on_child_added(world, canvas, e);
    return e;
}


ecs_entity_t spawn_ui_line2D_v2(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 point_a, const int2 point_b, const color line_color, const float thickness, const double life_time, const float2 parent_real_position, const int2 parent_position, const byte layer) {
    return spawn_ui_line2D(world, canvas, parent, point_a, point_b, float2_zero, float2_zero, line_color, thickness, life_time, parent_real_position, parent_position, layer);
}

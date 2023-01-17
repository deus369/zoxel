float2 get_ui_real_position2D_canvas_no_anchor(int2 local_pixel_position, float2 canvas_size_f, float aspect_ratio)
{
    return (float2) { 
            (2.0f * (local_pixel_position.x  / canvas_size_f.x) - 1.0f), // aspect_ratio,
            (2.0f * (local_pixel_position.y  / canvas_size_f.y) - 1.0f) };
}

void set_ui_line_position(LineData2D *lineData2D, const LineElementData *lineElementData, float2 canvas_size_f, float aspect_ratio)
{
    float2 point_a = get_ui_real_position2D_canvas_no_anchor(
        (int2) { lineElementData->value.x, lineElementData->value.y }, canvas_size_f, aspect_ratio);
    float2 point_b = get_ui_real_position2D_canvas_no_anchor(
        (int2) { lineElementData->value.z, lineElementData->value.w }, canvas_size_f, aspect_ratio);
    lineData2D->value = (float4) { point_a.x, point_a.y, point_b.x, point_b.y };
    // printf("Position3D of line set to: %fx%fx%fx%f from %ix%ix%ix%i\n",
    //    point_a.x, point_a.y, point_b.x, point_b.y,
    //    lineElementData->value.x, lineElementData->value.y, lineElementData->value.z, lineElementData->value.w);
    // lineData2D->value = (float4) { -1.0f, 0, 1.0f, 0 };
}

//! Sets real position when pixel position updates
/**
*   \done Make this instantaneous for children uis as well.
*   \todo This needs to also account for child uis
*   \todo Change queries still not working, make a better test function with more components.
*/
void Line2DElementSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    ecs_iter_t change_iter = ecs_query_iter(it->world, changeQuery);
    while (ecs_query_next(&change_iter))
    {
        if (change_iter.table != it->table)
        {
            ecs_query_skip(&change_iter);
        }
    }
    if (!ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    //! \todo Update this after getting a working example of change filters
    // printf("Line2DElementSystem changed query.\n");
    ecs_world_t *world = it->world;
    const LineElementData *lineElementDatas = ecs_field(it, LineElementData, 2);
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 3);
    LineData2D *lineData2Ds = ecs_field(it, LineData2D, 4);
    for (int i = 0; i < it->count; i++)
    {
        const CanvasLink *canvasLink = &canvasLinks[i];
        if (ecs_is_valid(world, canvasLink->value))
        {
            int2 canvas_size = ecs_get(world, canvasLink->value, PixelSize)->value;
            float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
            float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
            const LineElementData *lineElementData = &lineElementDatas[i];
            LineData2D *lineData2D = &lineData2Ds[i];
            // set render position based on canvas
            set_ui_line_position(lineData2D, lineElementData, canvas_size_f, aspect_ratio);
        }
    }
}
zoxel_declare_system(Line2DElementSystem);



/*float2 point_a = get_ui_real_position2D_canvas_no_anchor(
    (int2) { lineElementData->value.x, lineElementData->value.y }, canvas_size_f, aspect_ratio);
float2 point_b = get_ui_real_position2D_canvas_no_anchor(
    (int2) { lineElementData->value.z, lineElementData->value.w }, canvas_size_f, aspect_ratio);
lineData2D->value = (float4) { point_a.x, point_a.y, point_b.x, point_b.y };*/
ecs_entity_t prefab_ui_line2D;
ecs_entity_t prefab_temporary_ui_line2D;

void spawn_prefab_ui_line2D(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_ui_line2D");
    set_unique_entity_name(world, e, "prefab_ui_line2D");
    zoxel_add_tag(world, e, Line2D);
    zoxel_set(world, e, LineData2D, { { 0, 0, 0, 0 } });
    zoxel_set(world, e, LineElementData, { { 0, 0, 0, 0 } });
    zoxel_set(world, e, LineThickness, { 1 });
    zoxel_set(world, e, CanvasLink, { });
    zoxel_set(world, e, Layer2D, { 0 });    // use to render in order during ui render process
    zoxel_set(world, e, Color, { { 255, 0, 0, 255 } });
    // temp
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e);
    ecs_add_id(world, e2, EcsPrefab);
    set_unique_entity_name(world, e2, "prefab_temporary_ui_line2D");
    zoxel_set(world, e2, DestroyInTime, { 0 });
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log_arg("spawn_prefab ui_line2D [%lu].\n", (long int) (e));
    #endif
    prefab_ui_line2D = e;
    prefab_temporary_ui_line2D = e2;
}

extern void set_ui_line_position(LineData2D *lineData2D, const LineElementData *lineElementData, float2 canvas_size_f, float aspect_ratio);

ecs_entity_t spawn_ui_line2D(ecs_world_t *world, ecs_entity_t canvas, int2 point_a, int2 point_b, color line_color, float thickness, double life_time)
{
    ecs_defer_begin(world);
    ecs_entity_t e;
    if (life_time == 0.0)
    {
        // printf("Spawning ui_line2D!\n");
        e = ecs_new_w_pair(world, EcsIsA, prefab_ui_line2D);
    }
    else
    {
        // printf("Spawning temporary_ui_line2D! %f\n", life_time);
        e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_ui_line2D);
    }
    zoxel_set(world, e, Color, { line_color });
    // set_unique_entity_name(world, e, "line2D");
    ecs_set(world, e, LineThickness, { thickness });
    ecs_set(world, e, LineElementData, { { point_a.x, point_a.y, point_b.x, point_b.y } });
    int2 canvas_size = screen_dimensions;
    if (canvas != 0)
    {
        canvas_size = ecs_get(world, canvas, PixelSize)->value;
        ecs_set(world, e, CanvasLink, { canvas });
    }
    float2 canvas_size_f = { (float) canvas_size.x, (float) canvas_size.y };
    float aspect_ratio = canvas_size_f.x / canvas_size_f.y;
    const LineElementData lineElementData = (LineElementData) { { point_a.x, point_a.y, point_b.x, point_b.y } };
    LineData2D lineData2D;
    set_ui_line_position(&lineData2D, &lineElementData, canvas_size_f, aspect_ratio);
    ecs_set(world, e, LineData2D, { lineData2D.value });
    // temp stuff
    if (life_time != 0.0f)
    {
        ecs_set(world, e, DestroyInTime, { life_time });
    }
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log_arg("Spawned ui_line2D [%lu]\n", (long int) e);
    #endif
    return e;
}
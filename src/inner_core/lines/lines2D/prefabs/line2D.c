ecs_entity_t prefab_line2D;
extern ecs_entity_t prefab_temporary_line2D;

ecs_entity_t spawn_prefab_line2D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_line2D")
    zox_add_tag(e, Line2D)
    zox_prefab_set(e, LineData2D, {{ 0, 0, 0, 0 }})
    zox_prefab_set(e, LineThickness, { 1 })
    zox_prefab_set(e, Color, {{ 0, 255, 255, 255 }})
    zox_prefab_set(e, Layer2D, { 0 })
    prefab_line2D = e;
    return e;
}

ecs_entity_t spawn_line2D(ecs_world_t *world, const float2 pointA, const float2 pointB, const float thickness, const double life_time) {
    ecs_entity_t e;
    if (life_time == 0.0) e = ecs_new_w_pair(world, EcsIsA, prefab_line2D);
    else e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_line2D);
    zox_name("line2D")
    zox_set(e, LineData2D, { { pointA.x, pointA.y, pointB.x, pointB.y } })
    zox_set(e, LineThickness, { thickness })
    if (life_time != 0.0f) zox_set(e, DestroyInTime, { life_time })
    return e;
}

ecs_entity_t spawn_line2D_colored(ecs_world_t *world, const float2 pointA, const float2 pointB, const float thickness, const double life_time, const color_rgb line_color) {
    const ecs_entity_t e = spawn_line2D(world, pointA, pointB, thickness, life_time);
    zox_set(e, Color, { color_rgb_to_color(line_color) })
    return e;
}

void spawn_line2D_square(ecs_world_t *world, const float2 point, const float2 size, const float thickness, const double life_time) {
    spawn_line2D(world,
        float2_add(point, (float2) { -size.x / 2.0f, -size.y / 2.0f }),
        float2_add(point, (float2) { size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
    spawn_line2D(world,
        float2_add(point, (float2) { size.x / 2.0f, -size.y / 2.0f }),
        float2_add(point, (float2) { size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line2D(world,
        float2_add(point, (float2) { size.x / 2.0f, size.y / 2.0f }),
        float2_add(point, (float2) { -size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line2D(world,
        float2_add(point, (float2) { -size.x / 2.0f, size.y / 2.0f }),
        float2_add(point, (float2) { -size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
}

ecs_entity_t prefab_line3D;
ecs_entity_t prefab_temporary_line3D;

ecs_entity_t spawn_prefab_line3D(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_line3D")
    zox_add_tag(e, Line3D)
    zox_prefab_set(e, LineData3D, { { 0, 0, 0, 0, 0, 0 } })
    zox_prefab_set(e, LineThickness, { 1 })
    zox_prefab_set(e, DestroyInTime, { 0 })
    zox_prefab_set(e, ColorRGB, { { 22, 122, 44 } })
    prefab_line3D = e;
    return e;
}

ecs_entity_t spawn_line3D(ecs_world_t *world, const float3 pointA, const float3 pointB, const float thickness, const double life_time) {
    ecs_entity_t e;
    if (life_time == 0) e = ecs_new_w_pair(world, EcsIsA, prefab_line3D);
    else e = ecs_new_w_pair(world, EcsIsA, prefab_temporary_line3D);
    // zox_name("line3D")
    zox_set(e, LineData3D, { { pointA.x, pointA.y, pointA.z, pointB.x, pointB.y, pointB.z } })
    zox_set(e, LineThickness, { thickness })
    if (life_time != 0.0f) zox_set(e, DestroyInTime, { life_time })
    return e;
}

ecs_entity_t spawn_line3D_colored(ecs_world_t *world, const float3 pointA, const float3 pointB, const float thickness, const double life_time, const color_rgb line_color) {
    const ecs_entity_t e = spawn_line3D(world, pointA, pointB, thickness, life_time);
    zox_set(e, ColorRGB, { line_color })
    return e;
}

void render_line3D_thickness(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color, const float thickness) {
    spawn_line3D_colored(world, a, b, thickness, 0.01, line_color);
}

void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color) {
    spawn_line3D_colored(world, a, b, 4, 0.01, line_color);
}



/*void spawn_line3D_square(ecs_world_t *world, float3 point, float3 size, float thickness, double life_time) {
    spawn_line3D(world,
        float3_add(point, (float3) { -size.x / 2.0f, -size.y / 2.0f }),
        float3_add(point, (float3) { size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
    spawn_line3D(world,
        float3_add(point, (float3) { size.x / 2.0f, -size.y / 2.0f }),
        float3_add(point, (float3) { size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line3D(world,
        float3_add(point, (float3) { size.x / 2.0f, size.y / 2.0f }),
        float3_add(point, (float3) { -size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time);
    spawn_line3D(world,
        float3_add(point, (float3) { -size.x / 2.0f, size.y / 2.0f }),
        float3_add(point, (float3) { -size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time);
}*/

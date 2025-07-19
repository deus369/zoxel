void spawn_line2D_square(ecs_world_t *world,
    const float2 point,
    const float2 size,
    const float thickness,
    const double life_time,
    const color_rgb line_color)
{
    spawn_line2D_colored(world,
        float2_add(point, (float2) { -size.x / 2.0f, -size.y / 2.0f }),
        float2_add(point, (float2) { size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time, line_color);
    spawn_line2D_colored(world,
        float2_add(point, (float2) { size.x / 2.0f, -size.y / 2.0f }),
        float2_add(point, (float2) { size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time, line_color);
    spawn_line2D_colored(world,
        float2_add(point, (float2) { size.x / 2.0f, size.y / 2.0f }),
        float2_add(point, (float2) { -size.x / 2.0f, size.y / 2.0f }),
        thickness, life_time, line_color);
    spawn_line2D_colored(world,
        float2_add(point, (float2) { -size.x / 2.0f, size.y / 2.0f }),
        float2_add(point, (float2) { -size.x / 2.0f, -size.y / 2.0f }),
        thickness, life_time, line_color);
}
void spawn_arrow3D(ecs_world_t *world, const float3 point, const float3 normal, const float arrow_radius, const float thickness, const double life_time) {
    const float3 pointB = float3_add(point, normal);
    spawn_line3D(world, point, pointB, thickness, life_time);
    const float3 pointC = float3_sub(point, float3_multiply_float(normal, -0.1f));
    // todo: move arrow_radius along normal axis
    spawn_line3D(world, point, float3_add(pointC, (float3) { arrow_radius, 0, 0 }), thickness, life_time);
    spawn_line3D(world, point, float3_add(pointC, (float3) { -arrow_radius, 0, 0 }), thickness, life_time);
    spawn_line3D(world, point, float3_add(pointC, (float3) { 0, 0, arrow_radius }), thickness, life_time);
    spawn_line3D(world, point, float3_add(pointC, (float3) { 0, 0, -arrow_radius }), thickness, life_time);
}
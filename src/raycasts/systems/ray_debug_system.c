extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

void RayDebugSystem(ecs_iter_t *it) {
    const color_rgb debug_color = { 255, 55, 55 };
    const color_rgb debug_color2 = { 155, 155, 155 };
    const float ray_length = 16;
    zox_field_world()
    zox_field_in(RaycastOrigin, raycastOrigins, 1)
    zox_field_in(RaycastNormal, raycastNormals, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RaycastOrigin, raycastOrigins, origin)
        zox_field_i(RaycastNormal, raycastNormals, normal)
        float3 end_point = float3_multiply_float(normal->value, ray_length);
        float3 end_point2 = float3_multiply_float(float3_up, 1);
        render_line3D(world, origin->value, float3_add(origin->value, end_point), debug_color);
        render_line3D(world, origin->value, float3_add(origin->value, end_point2), debug_color2);
    }
} zox_declare_system(RayDebugSystem)

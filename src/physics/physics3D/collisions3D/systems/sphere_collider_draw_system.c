extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

void SphereColliderDrawSystem(ecs_iter_t *it) {
    zox_iter_world()
    const color_rgb line_color = (color_rgb) { 55, 55, 55 };
    zox_field_in(RenderDisabled, renderDisableds, 1)
    zox_field_in(Position3D, position3Ds, 2)
    zox_field_in(SphereRadius, sphereRadiuss, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(SphereRadius, sphereRadiuss, sphereRadius)
        // spawn_cube_lines(world, chunk_bounds.center, chunk_bounds.extents, 1, 1, line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { sphereRadius->value, 0, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { -sphereRadius->value, 0, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, sphereRadius->value, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, -sphereRadius->value, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, sphereRadius->value }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, -sphereRadius->value }), line_color);
    }
} zox_declare_system(SphereColliderDrawSystem)

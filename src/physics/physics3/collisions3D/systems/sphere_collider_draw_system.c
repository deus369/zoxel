extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

void SphereColliderDrawSystem(ecs_iter_t *it) {
    const color_rgb line_color = (color_rgb) { 55, 55, 55 };
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderDisabled)
    zox_sys_in(Position3D)
    zox_sys_in(SphereRadius)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(Position3D, position3D)
        zox_sys_i(SphereRadius, sphereRadius)
        if (renderDisabled->value) {
            continue;
        }
        // spawn_cube_lines(world, chunk_bounds.center, chunk_bounds.extents, 1, 1, line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { sphereRadius->value, 0, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { -sphereRadius->value, 0, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, sphereRadius->value, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, -sphereRadius->value, 0 }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, sphereRadius->value }), line_color);
        render_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0, -sphereRadius->value }), line_color);
    }
} zox_declare_system(SphereColliderDrawSystem)

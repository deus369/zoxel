extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

void FrustumDrawSystem(ecs_iter_t *it) {
    color_rgb debug_color = (color_rgb) { 0, 0, 0 };
    zox_iter_world()
    zox_field_in(FrustumCorners, frustumCornerss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(FrustumCorners, frustumCornerss, frustumCorners)
        draw_frustum(world, frustumCorners->value, debug_color);
    }
} zox_declare_system(FrustumDrawSystem)

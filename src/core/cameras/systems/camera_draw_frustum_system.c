void FrustumDrawSystem(ecs_iter_t *it) {
    color_rgb debug_color = (color_rgb) { 0, 0, 0 };
    zox_iter_world()
    zox_field_in(FrustumCorners, frustumCornerss, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(FrustumCorners, frustumCornerss, frustumCorners)
        // need a double3 version now
        // draw_frustum(world, frustumCorners->value, debug_color);
    }
} zox_declare_system(FrustumDrawSystem)

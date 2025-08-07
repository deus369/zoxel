void Friction2DSystem(iter *it) {
    const float frictionValue = 8.0f;  // 0.002
    zox_sys_begin()
    zox_sys_in(Velocity2D)
    zox_sys_out(Acceleration2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Velocity2D, velocity2D)
        zox_sys_o(Acceleration2D, acceleration2D)
        acceleration2D->value.x -= velocity2D->value.x * frictionValue;
        acceleration2D->value.y -= velocity2D->value.y * frictionValue;
    }
} zox_declare_system(Friction2DSystem)
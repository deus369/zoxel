void Friction2DSystem(ecs_iter_t *it) {
    const float frictionValue = 8.0f;  // 0.002
    zox_field_in(Velocity2D, velocity2Ds, 2)
    zox_field_out(Acceleration2D, acceleration2Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Velocity2D, velocity2Ds, velocity2D)
        zox_field_o(Acceleration2D, acceleration2Ds, acceleration2D)
        acceleration2D->value.x -= velocity2D->value.x * frictionValue;
        acceleration2D->value.y -= velocity2D->value.y * frictionValue;
    }
} zox_declare_system(Friction2DSystem)

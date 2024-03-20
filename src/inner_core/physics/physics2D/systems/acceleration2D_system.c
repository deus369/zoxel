void Acceleration2DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    zox_field_out(Velocity2D, velocity2Ds, 1)
    zox_field_out(Acceleration2D, acceleration2Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(Velocity2D, velocity2Ds, velocity2D)
        zox_field_i_out(Acceleration2D, acceleration2Ds, acceleration2D)
        velocity2D->value.x += acceleration2D->value.x * delta_time;
        velocity2D->value.y += acceleration2D->value.y * delta_time;
        float2_make_zero(&acceleration2D->value);
    }
} zox_declare_system(Acceleration2DSystem)

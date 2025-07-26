void Acceleration2DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(Velocity2D)
    zox_sys_out(Acceleration2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(Velocity2D, velocity2D)
        zox_sys_o(Acceleration2D, acceleration2D)
        velocity2D->value.x += acceleration2D->value.x * delta_time;
        velocity2D->value.y += acceleration2D->value.y * delta_time;
        float2_make_zero(&acceleration2D->value);
    }
} zox_declare_system(Acceleration2DSystem)

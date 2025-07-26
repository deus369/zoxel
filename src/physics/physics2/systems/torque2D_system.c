void Torque2DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(Rotation2D)
    zox_sys_in(Torque2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(Rotation2D, rotation2D)
        zox_sys_i(Torque2D, torque2D)
        rotation2D->value += torque2D->value * delta_time;
        if (rotation2D->value > 2 * M_PI) rotation2D->value -= 2 * M_PI;
    }
} zox_declare_system(Torque2DSystem)

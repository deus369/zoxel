void Torque2DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_out(Rotation2D, rotation2Ds, 1)
    zox_field_in(Torque2D, torque2Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(Rotation2D, rotation2Ds, rotation2D)
        zox_field_i(Torque2D, torque2Ds, torque2D)
        rotation2D->value += torque2D->value * delta_time;
        if (rotation2D->value > 2 * M_PI) rotation2D->value -= 2 * M_PI;
    }
} zox_declare_system(Torque2DSystem)

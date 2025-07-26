void InstanceRender2DSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(Position2D)
    zox_sys_in(Rotation2D)
    zox_sys_in(Scale1D)
    zox_sys_in(Brightness)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position2D, position2D)
        zox_sys_i(Rotation2D, rotation2D)
        zox_sys_i(Scale1D, scale1D)
        zox_sys_i(Brightness, brightness)
        render_instance2D(position2D->value, rotation2D->value, scale1D->value, brightness->value);
    }
} zox_declare_system(InstanceRender2DSystem)

void EulerOverrideSystem(ecs_iter_t *it) {
    zox_field_in(Euler, eulers, 2)
    zox_field_out(Rotation3D, rotations, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Euler, eulers, euler)
        zox_field_i_out(Rotation3D, rotations, rotation)
        rotation->value = quaternion_from_euler(euler->value);
    }
} zox_declare_system(EulerOverrideSystem)

void EulerOverrideSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(Euler)
    zox_sys_out(Rotation3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Euler, euler)
        zox_sys_o(Rotation3D, rotation)
        rotation->value = quaternion_from_euler(euler->value);
    }
} zoxd_system(EulerOverrideSystem)

void EulerLimitZSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(EulerLimitZ)
    zox_sys_out(Euler)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(EulerLimitZ, eulerLimitZ)
        zox_sys_o(Euler, euler)
        if (euler->value.z < eulerLimitZ->value.x) euler->value.z = eulerLimitZ->value.x;
        else if (euler->value.z > eulerLimitZ->value.y) euler->value.z = eulerLimitZ->value.y;
    }
} zoxd_system(EulerLimitZSystem)

void EulerLimitXSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(EulerLimitX)
    zox_sys_out(Euler)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(EulerLimitX, eulerLimitX)
        zox_sys_o(Euler, euler)
        if (euler->value.x < eulerLimitX->value.x) {
            euler->value.x = eulerLimitX->value.x;
        } else if (euler->value.x > eulerLimitX->value.y) {
            euler->value.x = eulerLimitX->value.y;
        }
    }
} zoxd_system(EulerLimitXSystem)

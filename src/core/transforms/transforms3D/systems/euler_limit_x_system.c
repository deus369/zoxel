void EulerLimitXSystem(ecs_iter_t *it) {
    zox_field_in(EulerLimitX, eulerLimitXs, 1)
    zox_field_out(Euler, eulers, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(EulerLimitX, eulerLimitXs, eulerLimitX)
        zox_field_i_out(Euler, eulers, euler)
        if (euler->value.x < eulerLimitX->value.x) euler->value.x = eulerLimitX->value.x;
        else if (euler->value.x > eulerLimitX->value.y) euler->value.x = eulerLimitX->value.y;
    }
} zox_declare_system(EulerLimitXSystem)

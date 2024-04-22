void EulerLimitZSystem(ecs_iter_t *it) {
    zox_field_in(EulerLimitZ, eulerLimitZs, 1)
    zox_field_out(Euler, eulers, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(EulerLimitZ, eulerLimitZs, eulerLimitZ)
        zox_field_i_out(Euler, eulers, euler)
        if (euler->value.z < eulerLimitZ->value.x) euler->value.z = eulerLimitZ->value.x;
        else if (euler->value.z > eulerLimitZ->value.y) euler->value.z = eulerLimitZ->value.y;
    }
} zox_declare_system(EulerLimitZSystem)

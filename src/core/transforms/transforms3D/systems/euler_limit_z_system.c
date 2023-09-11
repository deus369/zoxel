void EulerLimitZSystem(ecs_iter_t *it) {
    const EulerLimitZ *eulerLimitZs = ecs_field(it, EulerLimitZ, 1);
    Euler *eulers = ecs_field(it, Euler, 2);
    for (int i = 0; i < it->count; i++) {
        const EulerLimitZ *eulerLimitZ = &eulerLimitZs[i];
        Euler *euler = &eulers[i];
        if (euler->value.z < eulerLimitZ->value.x) euler->value.z = eulerLimitZ->value.x;
        else if (euler->value.z > eulerLimitZ->value.y) euler->value.z = eulerLimitZ->value.y;
    }
} zox_declare_system(EulerLimitZSystem)

void EulerLimitXSystem(ecs_iter_t *it) {
    const EulerLimitX *eulerLimitXs = ecs_field(it, EulerLimitX, 1);
    Euler *eulers = ecs_field(it, Euler, 2);
    for (int i = 0; i < it->count; i++) {
        const EulerLimitX *eulerLimitX = &eulerLimitXs[i];
        Euler *euler = &eulers[i];
        if (euler->value.x < eulerLimitX->value.x) euler->value.x = eulerLimitX->value.x;
        else if (euler->value.x > eulerLimitX->value.y) euler->value.x = eulerLimitX->value.y;
    }
} zox_declare_system(EulerLimitXSystem)
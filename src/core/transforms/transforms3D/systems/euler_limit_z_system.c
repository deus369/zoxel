void EulerLimitZSystem(ecs_iter_t *it) {
    const EulerLimitZ *eulerLimitZs = ecs_field(it, EulerLimitZ, 1);
    Euler *eulers = ecs_field(it, Euler, 2);
    for (int i = 0; i < it->count; i++) {
        Euler *euler = &eulers[i];
        const EulerLimitZ *eulerLimitZ = &eulerLimitZs[i];
        if (euler->value.z < eulerLimitZ->value.x) {
            euler->value.z = eulerLimitZ->value.x;
        }
        if (euler->value.z > eulerLimitZ->value.y) {
            euler->value.z = eulerLimitZ->value.y;
        }
        /*zoxel_log("euler limitations! [%fx%fx%f] - [%f-%f]\n",
            euler->value.x, euler->value.y, euler->value.z,
            eulerLimitZ->value.x, eulerLimitZ->value.y);*/
    }
}
zoxel_declare_system(EulerLimitZSystem)
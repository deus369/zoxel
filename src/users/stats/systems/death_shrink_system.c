void DeathShrinkSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    double time = zox_current_time;
    const Dead *deads = ecs_field(it, Dead, 1);
    const DiedTime *diedTimes = ecs_field(it, DiedTime, 2);
    Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    for (int i = 0; i < it->count; i++) {
        const Dead *dead = &deads[i];
        if (!dead->value) continue;
        const DiedTime *diedTime = &diedTimes[i];
        double death_time = time - diedTime->value;
        if (death_time < 0) death_time = 0;
        else if (death_time > 1) death_time = 1;
        Scale1D *scale1D = &scale1Ds[i];
        scale1D->value = float_lerp(1, 0, death_time);
    }
} zox_declare_system(DeathShrinkSystem)
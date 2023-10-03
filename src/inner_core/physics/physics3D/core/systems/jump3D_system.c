void Jump3DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    const Dead *deads = ecs_field(it, Dead, 1);
    Jump *jumps = ecs_field(it, Jump, 2);
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 3);
    for (int i = 0; i < it->count; i++) {
        const Dead *dead = &deads[i];
        if (dead->value) continue;
        Jump *jump = &jumps[i];
        if (jump->value == 0) continue;
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        acceleration3D->value.y += physics3D_jump;
        jump->value -= delta_time;
        if (jump->value < 0) jump->value = 0;
    } 
} zox_declare_system(Jump3DSystem)
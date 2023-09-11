void EulerOverrideSystem(ecs_iter_t *it) {
    const Euler *eulers = ecs_field(it, Euler, 2);
    Rotation3D *rotations = ecs_field(it, Rotation3D, 3);
    for (int i = 0; i < it->count; i++) {
        Rotation3D *rotation = &rotations[i];
        const Euler *euler = &eulers[i];
        rotation->value = quaternion_from_euler(euler->value);
    }
} zox_declare_system(EulerOverrideSystem)
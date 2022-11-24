//! Called in ecs updates
void EulerOverrideSystem(ecs_iter_t *it)
{
    const Euler *eulers = ecs_field(it, Euler, 2);
    Rotation *rotations = ecs_field(it, Rotation, 3);
    for (int i = 0; i < it->count; i++)
    {
        Rotation *rotation = &rotations[i];
        const Euler *euler = &eulers[i];
        rotation->value = quaternion_from_euler(euler->value);
    }
}
ECS_SYSTEM_DECLARE(EulerOverrideSystem);
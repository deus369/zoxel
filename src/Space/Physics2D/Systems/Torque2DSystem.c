// #include "../../../Imports/Flecs/flecs.h"
// #include "../../../Core/Transforms2D/Transforms2D.h"

void Torque2DSystem(ecs_iter_t *it)
{
    double deltaTime = (double) it->delta_time;
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 1);
    Torque2D *torque2Ds = ecs_field(it, Torque2D, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Torque2D *torque2D = &torque2Ds[i];
        Rotation2D *rotation2D = &rotation2Ds[i];
        rotation2D->value += torque2D->value * deltaTime;
        if (rotation2D->value > 2 * M_PI)
        {
            rotation2D->value -= 2 * M_PI;
        }
        // rotation2Ds = rotation2D;
    }
}
ECS_SYSTEM_DECLARE(Torque2DSystem);
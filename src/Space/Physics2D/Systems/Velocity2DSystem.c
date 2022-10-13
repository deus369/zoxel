// #include "../../../Imports/Flecs/flecs.h"
// #include "../Physics2D.h"
// #include "../../../Core/Core/Core.h"
// #include "../../../Core/Transforms2D/Transforms2D.h"

void Velocity2DSystem(ecs_iter_t *it)
{
    double deltaTime = (double) it->delta_time;
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Velocity2D *velocity2Ds = ecs_field(it, Velocity2D, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Velocity2D *velocity2D = &velocity2Ds[i];
        Position2D *position2D = &position2Ds[i];
        position2D->value.x += velocity2D->value.x * deltaTime;
        position2D->value.y += velocity2D->value.y * deltaTime;
    }
}
ECS_SYSTEM_DECLARE(Velocity2DSystem);
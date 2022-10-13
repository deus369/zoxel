//! Causes friction upon movement.
void Friction2DSystem(ecs_iter_t *it)
{
    double deltaTime = (double) it->delta_time;
    float frictionValue = 100 * 0.02f * deltaTime;
    Velocity2D *velocity2Ds = ecs_field(it, Velocity2D, 2);
    for (int i = 0; i < it->count; i++)
    {
        Velocity2D *velocity2D = &velocity2Ds[i];
        if (!(velocity2D->value.x == 0 && velocity2D->value.y == 0))
        {
            velocity2D->value.x -= velocity2D->value.x * frictionValue;
            velocity2D->value.y -= velocity2D->value.y * frictionValue;
            // velocity2D->value.y *= frictionValue;
        }
    }
}
ECS_SYSTEM_DECLARE(Friction2DSystem);
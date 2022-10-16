//! Causes friction upon movement.
void Friction2DSystem(ecs_iter_t *it)
{
    double deltaTime = (double) it->delta_time;
    const float frictionValue = 2.0f;  // 0.002
    const Velocity2D *velocity2Ds = ecs_field(it, Velocity2D, 2);
    Acceleration2D *acceleration2Ds = ecs_field(it, Acceleration2D, 3);
    for (int i = 0; i < it->count; i++)
    {
        const Velocity2D *velocity2D = &velocity2Ds[i];
        Acceleration2D *acceleration2D = &acceleration2Ds[i];
        acceleration2D->value.x -= velocity2D->value.x * frictionValue;
        acceleration2D->value.y -= velocity2D->value.y * frictionValue;
        // printf("Adding friction.\n");
    }
}
ECS_SYSTEM_DECLARE(Friction2DSystem);

        /*
        if (!(velocity2D->value.x == 0 && velocity2D->value.y == 0))
        {
            velocity2D->value.x -= velocity2D->value.x * frictionValue;
            velocity2D->value.y -= velocity2D->value.y * frictionValue;
            // velocity2D->value.y *= frictionValue;
        }*/
            // velocity2D->value.y *= frictionValue;
        /*if (velocity2D->value.x != 0)
        {
            acceleration2D->value.x -= velocity2D->value.x * frictionValue;
        }
        if (velocity2D->value.y != 0)
        {
            acceleration2D->value.y -= velocity2D->value.y * frictionValue;
        }*/
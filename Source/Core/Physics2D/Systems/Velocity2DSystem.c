//! Veloco Rapters!
void Velocity2DSystem(ecs_iter_t *it)
{
    const float2 bounds = { 2.2f, 1.2f };
    double deltaTime = (double) it->delta_time;
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    const Velocity2D *velocity2Ds = ecs_field(it, Velocity2D, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Velocity2D *velocity2D = &velocity2Ds[i];
        Position2D *position2D = &position2Ds[i];
        position2D->value.x += velocity2D->value.x * deltaTime;
        position2D->value.y += velocity2D->value.y * deltaTime;
        // bounds! Used atm to keep player within the start area
        if (position2D->value.x >= bounds.x)
        {
            position2D->value.x -= bounds.x * 2.0f;
        }
        if (position2D->value.x <= -bounds.x)
        {
            position2D->value.x += bounds.x * 2.0f;
        }
        if (position2D->value.y >= bounds.y)
        {
            position2D->value.y -= bounds.y * 2.0f;
        }
        if (position2D->value.y <= -bounds.y)
        {
            position2D->value.y += bounds.y * 2.0f;
        }
    }
}
ECS_SYSTEM_DECLARE(Velocity2DSystem);
//! Veloco Rapters!
void Velocity3DSystem(ecs_iter_t *it)
{
    // const float2 bounds = { 2.2f, 1.2f };
    double deltaTime = (double) it->delta_time;
    Position *positions = ecs_field(it, Position, 1);
    const Velocity *velocitys = ecs_field(it, Velocity, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Velocity *velocity = &velocitys[i];
        Position *position = &positions[i];
        position->value.x += velocity->value.x * deltaTime;
        position->value.y += velocity->value.y * deltaTime;
        position->value.z += velocity->value.z * deltaTime;
        // bounds! Used atm to keep player within the start area
        /*if (position->value.x >= bounds.x)
        {
            position->value.x -= bounds.x * 2.0f;
        }
        if (position->value.x <= -bounds.x)
        {
            position->value.x += bounds.x * 2.0f;
        }
        if (position->value.y >= bounds.y)
        {
            position->value.y -= bounds.y * 2.0f;
        }
        if (position->value.y <= -bounds.y)
        {
            position->value.y += bounds.y * 2.0f;
        }*/
    }
}
ECS_SYSTEM_DECLARE(Velocity3DSystem);
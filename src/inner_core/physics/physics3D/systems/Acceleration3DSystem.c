//! Adds force to the velocity per frame.Velocity
void Acceleration3DSystem(ecs_iter_t *it)
{
    double deltaTime = (double) it->delta_time;
    Velocity *velocitys = ecs_field(it, Velocity, 1);
    Acceleration *accelerations = ecs_field(it, Acceleration, 2);
    for (int i = 0; i < it->count; i++)
    {
        Acceleration *acceleration = &accelerations[i];
        Velocity *velocity = &velocitys[i];
        velocity->value.x += acceleration->value.x * deltaTime;
        velocity->value.y += acceleration->value.y * deltaTime;
        velocity->value.z += acceleration->value.z * deltaTime;
        acceleration->value.x = 0;
        acceleration->value.y = 0;
        acceleration->value.z = 0;
    }
}
ECS_SYSTEM_DECLARE(Acceleration3DSystem);
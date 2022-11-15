//! Adds force to the velocity per frame.
void Acceleration3DSystem(ecs_iter_t *it)
{
    double deltaTime = (double) it->delta_time;
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 1);
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 2);
    for (int i = 0; i < it->count; i++)
    {
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        Velocity3D *velocity3D = &velocity3Ds[i];
        velocity3D->value.x += acceleration3D->value.x * deltaTime;
        velocity3D->value.y += acceleration3D->value.y * deltaTime;
        velocity3D->value.z += acceleration3D->value.z * deltaTime;
        acceleration3D->value.x = 0;
        acceleration3D->value.y = 0;
        acceleration3D->value.z = 0;
    }
}
ECS_SYSTEM_DECLARE(Acceleration3DSystem);
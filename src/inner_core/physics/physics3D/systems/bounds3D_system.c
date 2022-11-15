//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Bounds3DSystem(ecs_iter_t *it)
{
    Position *position3Ds = ecs_field(it, Position, 1);
    const Bounds3D *bounds3Ds = ecs_field(it, Bounds3D, 2);
    for (int i = 0; i < it->count; i++)
    {
        Position *position3D = &position3Ds[i];
        const Bounds3D *bounds3D = &bounds3Ds[i];
        if (position3D->value.x >= bounds3D->value.x)
        {
            position3D->value.x -= bounds3D->value.x * 2.0f;
        }
        if (position3D->value.x <= -bounds3D->value.x)
        {
            position3D->value.x += bounds3D->value.x * 2.0f;
        }
        if (position3D->value.y >= bounds3D->value.y)
        {
            position3D->value.y -= bounds3D->value.y * 2.0f;
        }
        if (position3D->value.y <= -bounds3D->value.y)
        {
            position3D->value.y += bounds3D->value.y * 2.0f;
        }
        if (position3D->value.z >= bounds3D->value.z)
        {
            position3D->value.z -= bounds3D->value.z * 2.0f;
        }
        if (position3D->value.z <= -bounds3D->value.z)
        {
            position3D->value.z += bounds3D->value.z * 2.0f;
        }
    }
}
ECS_SYSTEM_DECLARE(Bounds3DSystem);
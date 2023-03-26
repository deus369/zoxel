//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Bounds3DSystem(ecs_iter_t *it) {
    const Bounds3D *bounds3Ds = ecs_field(it, Bounds3D, 1);
    Position3D *position3Ds = ecs_field(it, Position3D, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Bounds3D *bounds3D = &bounds3Ds[i];
        Position3D *position3D = &position3Ds[i];
        if (position3D->value.x > bounds3D->value.x)
        {
            position3D->value.x = bounds3D->value.x;
            // position3D->value.x -= bounds3D->value.x * 2.0f;
        }
        else if (position3D->value.x < -bounds3D->value.x)
        {
            position3D->value.x = -bounds3D->value.x;
            //position3D->value.x += bounds3D->value.x * 2.0f;
        }
        if (position3D->value.z > bounds3D->value.z)
        {
            position3D->value.z = bounds3D->value.z;
            //position3D->value.z -= bounds3D->value.z * 2.0f;
        }
        else if (position3D->value.z < -bounds3D->value.z)
        {
            position3D->value.z = -bounds3D->value.z;
            //position3D->value.z += bounds3D->value.z * 2.0f;
        }
        if (position3D->value.y > bounds3D->value.y)
        {
            position3D->value.y = bounds3D->value.y;
            //position3D->value.y -= bounds3D->value.y * 2.0f;
        }
        else if (position3D->value.y < -bounds3D->value.y)
        {
            position3D->value.y = -bounds3D->value.y;
            //position3D->value.y += bounds3D->value.y * 2.0f;
        }
        // printf("position3D [%fx%fx%f]\n", position3D->value.x, position3D->value.y, position3D->value.z);
    }
}
zoxel_declare_system(Bounds3DSystem)
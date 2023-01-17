//! Each entity will impact all other entities.
void Gravity3DSystem(ecs_iter_t *it)
{
    const Gravity3D *gravity3Ds = ecs_field(it, Gravity3D, 1);
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 2);
    for (int i = 0; i < it->count; i++)
    {
        const Gravity3D *gravity3D = &gravity3Ds[i];
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        acceleration3D->value.x += gravity3D->value.x;
        acceleration3D->value.y += gravity3D->value.y;
        acceleration3D->value.z += gravity3D->value.z;
    } 
}
zoxel_declare_system(Gravity3DSystem)
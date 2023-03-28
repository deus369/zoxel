//! Causes friction upon movement.
void Friction3DSystem(ecs_iter_t *it) {
    const float frictionValue = 8.0f;  // 0.002
    const Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 2);
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 3);
    for (int i = 0; i < it->count; i++) {
        const Velocity3D *velocity3D = &velocity3Ds[i];
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        acceleration3D->value.x -= velocity3D->value.x * frictionValue;
        acceleration3D->value.y -= velocity3D->value.y * frictionValue;
        acceleration3D->value.z -= velocity3D->value.z * frictionValue;
    }
}
zoxel_declare_system(Friction3DSystem)
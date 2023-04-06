//! Adds force to the velocity per frame.
void Acceleration3DSystem(ecs_iter_t *it) {
    // double delta_time = (double) it->delta_time;
    double delta_time = zoxel_delta_time;
    const Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 1);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 2);
    for (int i = 0; i < it->count; i++) {
        const Acceleration3D *acceleration3D = &acceleration3Ds[i];
        Velocity3D *velocity3D = &velocity3Ds[i];
        velocity3D->value.x += acceleration3D->value.x * delta_time;
        velocity3D->value.y += acceleration3D->value.y * delta_time;
        velocity3D->value.z += acceleration3D->value.z * delta_time;
    }
}
zoxel_declare_system(Acceleration3DSystem)
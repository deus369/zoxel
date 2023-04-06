//! Veloco Rapters!
void Velocity3DSystem(ecs_iter_t *it) {
    // const float2 bounds = { 2.2f, 1.2f };
    double delta_time = zoxel_delta_time;
    // double delta_time = (double) it->delta_time;
    Position3D *positions = ecs_field(it, Position3D, 1);
    const Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 2);
    for (int i = 0; i < it->count; i++) {
        const Velocity3D *velocity3D = &velocity3Ds[i];
        Position3D *position = &positions[i];
        position->value.x += velocity3D->value.x * delta_time;
        position->value.y += velocity3D->value.y * delta_time;
        position->value.z += velocity3D->value.z * delta_time;
    }
}
zoxel_declare_system(Velocity3DSystem)
void Acceleration3DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 1);
    Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 2);
    for (int i = 0; i < it->count; i++) {
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        Velocity3D *velocity3D = &velocity3Ds[i];
        velocity3D->value.x += acceleration3D->value.x * delta_time;
        velocity3D->value.y += acceleration3D->value.y * delta_time;
        velocity3D->value.z += acceleration3D->value.z * delta_time;
        acceleration3D->value.x = 0;
        acceleration3D->value.y = 0;
        acceleration3D->value.z = 0;
    }
}
zox_declare_system(Acceleration3DSystem)
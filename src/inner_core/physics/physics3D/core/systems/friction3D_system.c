// todo: only do this when scraping against a surface
void Friction3DSystem(ecs_iter_t *it) {
    const Velocity3D *velocity3Ds = ecs_field(it, Velocity3D, 2);
    Acceleration3D *acceleration3Ds = ecs_field(it, Acceleration3D, 3);
    for (int i = 0; i < it->count; i++) {
        const Velocity3D *velocity3D = &velocity3Ds[i];
        Acceleration3D *acceleration3D = &acceleration3Ds[i];
        acceleration3D->value.x -= velocity3D->value.x * friction3D;
        // acceleration3D->value.y -= velocity3D->value.y * friction3D;
        acceleration3D->value.z -= velocity3D->value.z * friction3D;
    }
} zox_declare_system(Friction3DSystem)
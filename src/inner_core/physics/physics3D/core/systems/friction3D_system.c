// todo: only do this when scraping against a surface
void Friction3DSystem(ecs_iter_t *it) {
    zox_field_in(Velocity3D, velocity3Ds, 2)
    zox_field_out(Acceleration3D, acceleration3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Velocity3D, velocity3Ds, velocity3D)
        zox_field_i_out(Acceleration3D, acceleration3Ds, acceleration3D)
        acceleration3D->value.x -= velocity3D->value.x * friction3D;
        // acceleration3D->value.y -= velocity3D->value.y * friction3D;
        acceleration3D->value.z -= velocity3D->value.z * friction3D;
    }
} zox_declare_system(Friction3DSystem)

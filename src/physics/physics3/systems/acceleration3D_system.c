void Acceleration3DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_out(Acceleration3D, acceleration3Ds, 1)
    zox_field_out(Velocity3D, velocity3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(Acceleration3D, acceleration3Ds, acceleration3D)
        zox_field_o(Velocity3D, velocity3Ds, velocity3D)
        velocity3D->value.x += acceleration3D->value.x * delta_time;
        velocity3D->value.y += acceleration3D->value.y * delta_time;
        velocity3D->value.z += acceleration3D->value.z * delta_time;
        float3_make_zero(&acceleration3D->value);
    }
} zox_declare_system(Acceleration3DSystem)

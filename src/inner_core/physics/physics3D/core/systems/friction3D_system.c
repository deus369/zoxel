void Friction3DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_in(Grounded, groundeds, 1)
    zox_field_in(Velocity3D, velocity3Ds, 2)
    zox_field_out(Acceleration3D, acceleration3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Grounded, groundeds, grounded)
        zox_field_i_in(Velocity3D, velocity3Ds, velocity3D)
        zox_field_i_out(Acceleration3D, acceleration3Ds, acceleration3D)
        float friction_power = friction3D;
        if (!grounded->value) friction_power = air_friction3D;
        float3_add_float3_p(&acceleration3D->value, float3_multiply_float(velocity3D->value, - friction_power * delta_time));
    }
} zox_declare_system(Friction3DSystem)

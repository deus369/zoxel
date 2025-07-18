void Friction3DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(Grounded)
    zox_sys_out(Velocity3D)
    zox_sys_out(Acceleration3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Grounded, grounded)
        zox_sys_o(Velocity3D, velocity3D)
        zox_sys_o(Acceleration3D, acceleration3D)
        float friction_power = grounded->value ? friction3D : air_friction3D;
        // Clamp friction to prevent exponential explosion
        //friction_power = clampf(friction_power, 0.0f, 1.0f);
        // Dampen velocity based on delta_time
        float friction_factor = 1.0f - (friction_power * delta_time);

        friction_factor = clampf(friction_factor, 0.0f, 1.0f); // Safety clamp

        velocity3D->value = float3_multiply_float(velocity3D->value, friction_factor);

        /*float speed = float3_length(velocity3D->value);
        if (speed < 0.1f) {
            velocity3D->value = float3_zero(); // Stop tiny drift
        }*/

    }
} zox_declare_system(Friction3DSystem)

/*float friction_power = friction3D;
if (!grounded->value) {
    friction_power = air_friction3D;
}
float3_add_float3_p(&acceleration3D->value, float3_multiply_float(velocity3D->value, - friction_power * delta_time));*/
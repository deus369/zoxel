void Dissipation3System(iter *it) {
    const float dissipation_rate = 2.0f; // tweak for stronger or weaker drag
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(Omega3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(Omega3D, omega)
        //float friction_factor = 1.0f - (dissipate_power * delta_time);
        //friction_factor = clampf(friction_factor, 0.0f, 1.0f); // Safety clamp
        //omega->value = float3_scale(omega->value, friction_factor);
        // Compute exponential decay factor
        float drag = expf(-dissipation_rate * delta_time);
        drag = clampf(drag, 0.0f, 1.0f); // Safety clamp
        omega->value = float3_scale(omega->value, drag);
    }
} zoxd_system(Dissipation3System)

/*float friction_power = friction3D;
if (!grounded->value) {
    friction_power = air_friction3D;
}
float3_add_float3_p(&acceleration3D->value, float3_scale(velocity3D->value, - friction_power * delta_time));*/
/*void Dissipation3System(iter *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(Omega3D)
    zox_sys_out(Alpha3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(Omega3D, omega)
        zox_sys_o(Alpha3D, alpha)
        if (float4_equals(omega->value, quaternion_identity)) {
            continue;
        }



        // e.g. 5% friction per second → 1- exp(-k dt)
        float k = rotation_friction;
        float factor = 1.0f - expf(-k * delta_time);

        // slerp current spin toward no spin
        omega->value = quaternion_slerp(omega->value, quaternion_identity, factor);

        // if it’s tiny, zero it out
        if (quaternion_angle(omega->value) < dissipation_threshold) {
            omega->value = quaternion_identity;
        }


    }
} zoxd_system(Dissipation3System)*/


        /*float magnitude = sqrt(omega3D->value.x * omega3D->value.x + omega3D->value.y * omega3D->value.y + omega3D->value.z * omega3D->value.z + omega3D->value.w * omega3D->value.w);
        if (magnitude < dissipation_threshold) {
            continue;
        }
        float factor = (-rotation_friction * magnitude) / (magnitude * magnitude + 1e-6);
        float3 euler = quaternion_to_euler(omega3D->value);
        float3_scale_p(&euler, factor);
        float4 dissipation = quaternion_from_euler(euler);
        quaternion_rotate_quaternion_p(&alpha3D->value, dissipation);*/
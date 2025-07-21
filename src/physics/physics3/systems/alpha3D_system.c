void Alpha3System(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_out(Alpha3D)
    zox_sys_out(Omega3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(Alpha3D, alpha)
        zox_sys_o(Omega3D, omega)
        omega->value = float3_add(omega->value, float3_scale(alpha->value, delta_time));
        float3_make_zero(&alpha->value);
    }
} zox_declare_system(Alpha3System)


        /*if (float4_equals(alpha->value, quaternion_identity)) {
            continue;
        }

        // extract accel axis & angle per second^2
        float accelAngle = 2.0f * acosf(alpha->value.w);
        float s1         = sqrtf(1.0f - alpha->value.w * alpha->value.w);
        float3 accelAxis = (s1 < 1e-6f)
        ? (float3){1,0,0}
        : float3_scale((float3) {alpha->value.x, alpha->value.y, alpha->value.z}, 1.0f / s1);

        // convert to delta‐omega
        float deltaAng = accelAngle * delta_time;
        float4 deltaQ = quaternion_from_axis_angle(accelAxis, deltaAng);

        quaternion_rotate_quaternion_p(&omega->value, deltaQ);

        // reset for next frame
        alpha->value = quaternion_identity;*/


        /*float magnitude = quaternion_magnitude(alpha->value);
        if (magnitude) {
            float4 delta_omega = get_delta_rotation(alpha->value, magnitude, delta_time);
            quaternion_rotate_quaternion_p(&omega->value, delta_omega);
        }
        alpha->value = quaternion_identity;*/

void Omega3System(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(Omega3D)
    zox_sys_out(Rotation3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Omega3D, omega)
        zox_sys_o(Rotation3D, rotation)

        float3 w = omega->value;       // angular velocity vector in radians/sec

        float omegaMag = float3_length(w);
        if (omegaMag < 1e-6f) {
            continue;   // no rotation this frame
        }

        // Normalize axis
        float3 axis = float3_scale(w, 1.0f / omegaMag);

        // Compute frame rotation angle
        float frameAngle = omegaMag * delta_time;

        // Compute delta quaternion for this frame
        float4 deltaQ = quaternion_from_axis_angle(axis, frameAngle);

        // Integrate rotation by multiplying current rotation by deltaQ
        quaternion_rotate_quaternion_p(&rotation->value, deltaQ);

        // Optional: normalize rotation quaternion after integration
        float invLen = 1.0f / sqrtf(
            rotation->value.x * rotation->value.x +
            rotation->value.y * rotation->value.y +
            rotation->value.z * rotation->value.z +
            rotation->value.w * rotation->value.w
        );

        rotation->value.x *= invLen;
        rotation->value.y *= invLen;
        rotation->value.z *= invLen;
        rotation->value.w *= invLen;

    }
} zox_declare_system(Omega3System)
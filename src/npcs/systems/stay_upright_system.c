/*void StayUprightSystem(ecs_iter_t *it) {
    const float kP = 3.5f;              // a bit stronger correction
    const float kD = 1.0f;              // stronger damping for snappy response
    const float max_upright_torque = 10.0f;

    zox_sys_world()
    zox_sys_begin()

    zox_sys_in(Rotation3D)
    zox_sys_in(Omega3D)
    zox_sys_out(Alpha3D)

    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Rotation3D, rotation)
        zox_sys_i(Omega3D, omega)
        zox_sys_o(Alpha3D, alpha)

        float4 q = rotation->value;

        // Normalize quaternion
        float invLen = 1.0f / sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        q.x *= invLen; q.y *= invLen; q.z *= invLen; q.w *= invLen;

        float3 up = quaternion_rotate_vector(q, (float3){0, 1, 0});

        float3 torqueAxis = float3_cross(up, (float3){0, 1, 0});
        float torqueMag = float3_length(torqueAxis);

        if (torqueMag < 0.0001f) {
            alpha->value = (float4){0, 0, 0, 0};
            continue;
        }

        float3 torqueDir = float3_scale(torqueAxis, 1.0f / torqueMag);

        // Extract xyz angular velocity from omega float4
        float3 angularVel = { omega->value.x, omega->value.y, omega->value.z };

        // Damping only on pitch and roll (x,z)
        float3 damping = {
            -kD * angularVel.x,
            0.0f,           // no damping on yaw
            -kD * angularVel.z
        };

        float pTerm = clampf(torqueMag * kP, -max_upright_torque, max_upright_torque);

        float3 torque = float3_add(float3_scale(torqueDir, pTerm), damping);


        float4 torque_quat_x = quaternion_from_axis_angle((float3) {1, 0, 0}, torque.x);
        alpha->value = quaternion_rotate(alpha->value, torque_quat_x);


        float4 torque_quat_z = quaternion_from_axis_angle((float3) {0, 0, 1}, torque.z);
        alpha->value = quaternion_rotate(alpha->value, torque_quat_z);

    }
} zoxd_system(StayUprightSystem)
*/
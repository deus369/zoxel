static inline float wrap_angle(float angle) {
    return remainderf(angle, 2.0f * M_PI);
}

void RotateTowardsSystem(ecs_iter_t *it) {
    const float kP = 4.0f;          // Stronger response to error
    const float kD = 0.5f;          // Still some damping
    const double max_torque = 15.0; // Let the bird *turn*, dammit

    zox_sys_world()
    zox_sys_begin()

    zox_sys_in(RotateTowards)
    zox_sys_in(DisableMovement)
    zox_sys_in(Position3D)
    zox_sys_in(Rotation3D)
    zox_sys_in(Omega3D)
    zox_sys_in(TargetPosition)
    zox_sys_out(Alpha3D)

    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RotateTowards, rotateTowards)
        zox_sys_i(DisableMovement, disable)
        zox_sys_i(Position3D, position)
        zox_sys_i(Rotation3D, rotation)
        zox_sys_i(Omega3D, omega)
        zox_sys_i(TargetPosition, target)
        zox_sys_o(Alpha3D, alpha)

        // only face target when commanded to
        if (disable->value || !rotateTowards->value) {
            continue;
        }

        // 1) World‑space look direction
        float3 dir = float3_subtract(target->value, position->value);
        dir.y = 0;
        float len = float3_length(dir) + 1e-3f;
        float3 lookDir = float3_scale(dir, 1.0f / len);

        // 2) Yaw error in [-π, π]
        float desiredYaw = atan2f(lookDir.x, lookDir.z);
        float currentYaw = quaternion_to_euler_y2(rotation->value);
        float rawErr     = desiredYaw - currentYaw;
        // float yawErr     = zox_fmod(rawErr + M_PI, 2.0f * M_PI) - M_PI;
        float yawErr = wrap_angle(rawErr);

        // 3) Angular velocity around Y axis (yaw rate)
        float currentRate = omega->value.y;

        // Skip if aligned and steady
        if (fabsf(yawErr) < 0.01f && fabsf(currentRate) < 0.01f) {
            continue;
        }

        // 4) PD control: τ = kP * error − kD * rate
        float scaled_kP = kP; // kP * clampf(fabsf(yawErr) / (M_PI * 0.25f), 0.2f, 1.0f);

        float torque_y = scaled_kP * yawErr - kD * currentRate;
        torque_y = clampf(torque_y, -max_torque, max_torque);

        // 5) Set alpha (angular acceleration) around Y axis
        alpha->value.y += torque_y;

        if (is_debug_rotate_towards) {
            const float debug_len = 1.0f;
            float3 start = position->value;
            float3 end   = float3_add(start, float3_scale(lookDir, debug_len));
            debug_linec(world, start, end, color_rgb_red);
        }

    }
} zoxd_system(RotateTowardsSystem)
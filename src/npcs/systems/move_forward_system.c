void MoveForwardSystem(ecs_iter_t *it) {
    const float target_angle = 45;
    const float min_dot_threshold = target_angle * degrees_to_radians; // 0.866f; // cos(30°)
    const float slow_down_distance = 1.5f;
    // TODO: Base Stop Threshold on Bounds3D
    const float stop_threshold = 0.45f;      // hard stop zone
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(MoveForwards)
    zox_sys_in(DisableMovement)
    zox_sys_in(Position3D)
    zox_sys_in(Rotation3D)
    // zox_sys_in(Velocity3D)
    zox_sys_in(TargetPosition)
    zox_sys_in(MoveSpeed)
    zox_sys_out(Acceleration3D)

    for (int i = 0; i < it->count; i++) {

        zox_sys_i(MoveForwards, moveForwards)
        zox_sys_i(DisableMovement, disable)
        zox_sys_i(Position3D, position)
        zox_sys_i(Rotation3D, rotation)
        // zox_sys_i(Velocity3D, velocity)
        zox_sys_i(TargetPosition, target)
        zox_sys_i(MoveSpeed, moveSpeed)
        zox_sys_o(Acceleration3D, acceleration)

        // only face target when commanded to
        if (disable->value || !moveForwards->value) {
            continue;
        }

        // Direction to target
        float3 to_target = float3_subtract(target->value, position->value);
        float distance = float3_length(to_target);
        float3 to_target_dir = float3_normalize(to_target);
        float3 forward = float4_rotate_float3(rotation->value, (float3) { 0, 0, 1 });

        // Dot product: how aligned are we?
        float dot = float3_dot(forward, to_target_dir);
        byte facing_target = dot > min_dot_threshold;
        byte is_near_target = distance < stop_threshold;

        if (is_debug_move_forwards) {
            // forward line
            float3 forward_line_end = float3_add(position->value, float3_scale(forward, 1.5f));
            debug_linec(world, position->value, forward_line_end, color_rgb_black);
            // Direction to target
            float3 target_line_end = float3_add(position->value, float3_scale(to_target_dir, 1.5f));
            debug_linec(world, position->value, target_line_end, facing_target ? color_rgb_green : color_rgb_red);
            float3 above_me = float3_add(position->value, float3_up);
            debug_linec(world, position->value, above_me, is_near_target ? color_rgb_red : color_rgb_cyan);

            // Visualize the dot threshold angle as a cone
            //float3 right = { 1, 0, 0 };
            //float3 up    = { 0, 1, 0 };

            // Rotate a vector by +min angle around Y
            float3 threshold_vector_pos = {
                sinf(min_dot_threshold) * forward.z + cosf(min_dot_threshold) * forward.x,
                0,
                cosf(min_dot_threshold) * forward.z - sinf(min_dot_threshold) * forward.x,
            };
            float3 threshold_end_pos = float3_add(position->value, float3_scale(float3_normalize(threshold_vector_pos), 1.5f));
            debug_linec(world, position->value, threshold_end_pos, color_rgb_black);

            // Mirror the vector to -min angle
            float3 threshold_vector_neg = {
                -sinf(min_dot_threshold) * forward.z + cosf(min_dot_threshold) * forward.x,
                0,
                cosf(min_dot_threshold) * forward.z + sinf(min_dot_threshold) * forward.x,
            };
            float3 threshold_end_neg = float3_add(position->value, float3_scale(float3_normalize(threshold_vector_neg), 1.5f));
            debug_linec(world, position->value, threshold_end_neg, color_rgb_black);
        }

        if (is_near_target|| !facing_target) {
            continue;
        }

        // Smooth deceleration near target
        float slowdown = fminf(1.0f, (distance - stop_threshold) / (slow_down_distance - stop_threshold));
        float3 movement_force = float3_scale(forward, moveSpeed->value * slowdown);
        acceleration->value = float3_add(acceleration->value, movement_force);
    }
} zoxd_system(MoveForwardSystem)
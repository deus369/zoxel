void FleeSystem(ecs_iter_t *it) {
    const float flee_distance    = 4.0f;  // how far we want to flee
    const float jitter_power     = 0.4f;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Behaviour)
    zox_sys_in(DisableMovement)
    zox_sys_in(Position3D)
    zox_sys_in(ThreatPosition)
    zox_sys_out(TargetPosition)

    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Behaviour, behaviour)
        zox_sys_i(DisableMovement, disable)
        zox_sys_i(Position3D, position)
        zox_sys_i(ThreatPosition, threat)
        zox_sys_o(TargetPosition, target)

        // only flee if in “wander” mode and not frozen
        if (disable->value || behaviour->value != zox_behaviour_flee) {
            continue;
        }

        // Compute flee direction
        float3 away = float3_subtract(position->value, threat->value);
        float dist = float3_length(away) + 0.001f;
        float3 dir = float3_scale(away, 1.0f / dist);

        // Add chaos
        float2 jitter = {
            ((rand() % 100) * 0.01f - 0.5f) * jitter_power,
            ((rand() % 100) * 0.01f - 0.5f) * jitter_power
        };

        float3 flee_direction = {
            dir.x + jitter.x,
            0,
            dir.z + jitter.y
        };

        flee_direction = float3_normalize(flee_direction);
        float3 flee_target = float3_add(position->value, float3_scale(flee_direction, flee_distance));

        // Set new target position
        target->value = flee_target;

        if (is_debug_flee) {
            const float debug_length = 1.0f;
            float3 start = position->value;

            // Show flee direction
            debug_linec(world, start, float3_add(start, float3_scale(flee_direction, debug_length)), color_rgb_black);
            // Line to threat
            debug_linec(world, start, threat->value, color_rgb_white);
            // Target line
            debug_linec(world, start, target->value, color_rgb_red);

            // 3) World‑space axes for reference
            // X axis in red
            /*debug_linec(world, start, float3_add(start, (float3){debug_length,0,0}), color_rgb_red);
            // Z axis in blue
            debug_linec(world, start, float3_add(start, (float3){0,0,debug_length}), color_rgb_blue);

            // 4) Y‑up check (green)
            debug_linec(world, start, float3_add(start, (float3){0,debug_length,0}), color_rgb_green);*/
        }
    }
} zoxd_system(FleeSystem)
void WanderSystem(ecs_iter_t *it) {
    init_delta_time()
    const float wander_length    = 5.0f;  // units per second
    const float vertical_bias   = 0.0f;   // how much to allow vertical wandering (usually 0 in flatland)
    const float jitter_power    = 15 * delta_time;   // chaos factor
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Behaviour)
    zox_sys_in(DisableMovement)
    zox_sys_in(Position3D)
    zox_sys_out(TargetPosition)
    zox_sys_out(WanderDirection)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Behaviour, behaviour)
        zox_sys_i(DisableMovement, disable)
        zox_sys_i(Position3D, position)
        zox_sys_o(TargetPosition, target)
        zox_sys_o(WanderDirection, wander)

        // only wander if in “wander” mode and not frozen
        if (disable->value || behaviour->value != zox_behaviour_wander) {
            continue;
        }

        // Jittery direction vector
        float2 jitter = {
            ((rand() % 100) * 0.01f - 0.5f) * jitter_power,
            ((rand() % 100) * 0.01f - 0.5f) * jitter_power
        };

        float3 jitter_vec = {
            jitter.x,
            vertical_bias,
            jitter.y
        };
        wander->value = float3_add(wander->value, jitter_vec);
        wander->value = float3_normalize(wander->value);

        // Move slightly in that direction
        target->value = float3_add(position->value, float3_scale(wander->value, wander_length));

        if (is_debug_wander) {
            const float debug_length = 1.0f;
            float3 start = position->value;
            debug_linec(world, start, float3_add(start, float3_scale(wander->value, debug_length)), color_rgb_yellow);
            debug_linec(world, start, target->value, color_rgb_cyan);
        }
    }
} zox_declare_system(WanderSystem)





// simple wander, adds acceleration to entity's with wander tag
// similar to player, make move forward, make rotate randomly

// todo: make similar to flee, just set target position randomly
/*void WanderSystem(ecs_iter_t *it) {
    const float2 movement_power = (float2) { 0, 4 };
    const float2 max_velocity = { 60 * 60, 160 * 60 };
    const double max_rotate_speed = 0.2; //  0.23;
    const float rotate_power = 0.8f;
    const float pivot_power = 0.4f;
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(Behaviour)
    zox_sys_in(DisableMovement)
    zox_sys_in(Rotation3D)
    zox_sys_in(Velocity3D)
    zox_sys_in(Omega3D)
    zox_sys_out(Acceleration3D)
    zox_sys_out(Alpha3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Behaviour, behaviour)
        zox_sys_i(DisableMovement, disableMovement)
        zox_sys_i(Rotation3D, rotation3D)
        zox_sys_i(Velocity3D, velocity3D)
        zox_sys_i(Omega3D, omega3D)
        zox_sys_o(Acceleration3D, acceleration3D)
        zox_sys_o(Alpha3D, alpha3D)
        if (disableMovement->value || behaviour->value != zox_behaviour_wander) {
            continue;
        }
        // float2 movement = { (rand() % 100) * 0.01f, (rand() % 100) * 0.01f };
        float2 movement = { (rand() % 100) * 0.01f * pivot_power - pivot_power * 0.5f, (rand() % 100) * 0.01f };
        float2 euler = { 0, (rand() % 100) * 0.01f * rotate_power - rotate_power * 0.5f };
        float3 move_vector = float4_rotate_float3(rotation3D->value, (float3) { movement.x, 0, movement.y });
        float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
        if (float_abs(rotated_velocity.x) < max_velocity.x * delta_time) {
            acceleration3D->value.x += move_vector.x * movement_power.x;
        }
        if (float_abs(rotated_velocity.z) < max_velocity.y * delta_time) {
            acceleration3D->value.z += move_vector.z * movement_power.y;
        }
        // rotate
        if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) || (euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed)) {
            quaternion_rotate_quaternion_p(&alpha3D->value, float2_to_rotation(euler));
        }
    }
} zox_declare_system(WanderSystem)*/


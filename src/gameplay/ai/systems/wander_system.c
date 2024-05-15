// simple wander, adds acceleration to entity's with wander tag
void WanderSystem(ecs_iter_t *it) {
    const float2 movement_power = (float2) { 0, 4 };
    const float2 max_velocity = { 60 * 60, 160 * 60 };
    const double max_rotate_speed = 0.2; //  0.23;
    const float rotate_power = 0.8f;
    const float pivot_power = 0.4f;
    double delta_time = zox_delta_time;
    // zox_iter_world()
    // similar to player, make move forward, make rotate randomly
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(Velocity3D, velocity3Ds, 3)
    zox_field_out(Acceleration3D, acceleration3Ds, 4)
    zox_field_in(Omega3D, omega3Ds, 5)
    zox_field_out(Alpha3D, alpha3Ds, 6)
    zox_field_out(Dead, deads, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Dead, deads, dead)
        if (dead->value) continue;
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_in(Velocity3D, velocity3Ds, velocity3D)
        zox_field_i_out(Acceleration3D, acceleration3Ds, acceleration3D)
        zox_field_i_in(Omega3D, omega3Ds, omega3D)
        zox_field_i_out(Alpha3D, alpha3Ds, alpha3D)
        // float2 movement = { (rand() % 100) * 0.01f, (rand() % 100) * 0.01f };
        float2 movement = { (rand() % 100) * 0.01f * pivot_power - pivot_power * 0.5f, (rand() % 100) * 0.01f };
        float2 euler = { 0, (rand() % 100) * 0.01f * rotate_power - rotate_power * 0.5f };
        float3 move_vector = float4_rotate_float3(rotation3D->value, (float3) { movement.x, 0, movement.y });
        float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
        if (float_abs(rotated_velocity.x) < max_velocity.x * delta_time) acceleration3D->value.x += move_vector.x * movement_power.x;
        if (float_abs(rotated_velocity.z) < max_velocity.y * delta_time) acceleration3D->value.z += move_vector.z * movement_power.y;
        // rotate
        if ((euler.y > 0 && quaternion_to_euler_y(omega3D->value) < max_rotate_speed) || (euler.y < 0 && quaternion_to_euler_y(omega3D->value) > -max_rotate_speed)) {
            float4 quaternion = float2_to_rotation(euler);
            quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
        }
    }
} zox_declare_system(WanderSystem)

void Jump3DSystem(ecs_iter_t *it) {
    const float jump_power = zox_jump_power;
    init_delta_time()
    zox_field_world()
    zox_field_in(DisableMovement, disableMovements, 1)
    zox_field_in(Velocity3D, velocity3Ds, 2)
    zox_field_out(Jump, jumps, 3)
    zox_field_out(Acceleration3D, acceleration3Ds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DisableMovement, disableMovements, disableMovement)
        zox_field_i(Velocity3D, velocity3Ds, velocity3D)
        zox_field_o(Jump, jumps, jump)
        if (disableMovement->value || !jump->value) {
            continue;
        }
        zox_field_o(Acceleration3D, acceleration3Ds, acceleration3D)
        float potential_velocity = velocity3D->value.y + (acceleration3D->value.y + jump_power) * delta_time;
        if (potential_velocity < max_jump_velocity) {
            acceleration3D->value.y += jump_power;
        }
        jump->value -= delta_time;
        if (jump->value < 0) {
            jump->value = 0;
        }
    } 
} zox_declare_system(Jump3DSystem)
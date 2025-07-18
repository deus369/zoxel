void Jump3System(ecs_iter_t *it) {
    const float jump_power = zox_jump_power;
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(DisableMovement)
    zox_sys_out(Velocity3D)
    zox_sys_out(Jump)
    zox_sys_out(Acceleration3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DisableMovement, disableMovement)
        zox_sys_o(Velocity3D, velocity3)
        zox_sys_o(Jump, jump)
        zox_sys_o(Acceleration3D, acceleration3D)
        if (disableMovement->value || !jump->value) {
            continue;
        }

        if (jump->value > 0) {
            velocity3->value.y = jump_power; // Fixed jump impulse
        }

        /*float potential_velocity = velocity3->value.y + (acceleration3D->value.y + jump_power) * delta_time;
        if (potential_velocity < max_jump_velocity) {
            acceleration3D->value.y += jump_power;
        }*/
        jump->value -= delta_time;
        if (jump->value < 0) {
            jump->value = 0;
        }
    } 
} zox_declare_system(Jump3System)
void Jump3VelSystem(ecs_iter_t *it) {
    const float jump_power = zox_jump_power;
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(DisableMovement)
    zox_sys_out(Velocity3D)
    zox_sys_out(Jump)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DisableMovement, disableMovement)
        zox_sys_o(Velocity3D, velocity3)
        zox_sys_o(Jump, jump)
        if (disableMovement->value || !jump->value) {
            continue;
        }

        if (jump->value > 0) {
            velocity3->value.y = jump_power; // Jump impulse
        }

        jump->value -= delta_time;
        if (jump->value < 0) {
            jump->value = 0;
        }
    } 
} zoxd_system(Jump3VelSystem)

// this is having issues now due to new collision detect
void Jump3AccSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(DisableMovement)
    zox_sys_in(Velocity3D)
    zox_sys_out(Acceleration3D)
    zox_sys_out(Jump)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DisableMovement, disableMovement)
        zox_sys_i(Velocity3D, vel)
        zox_sys_o(Acceleration3D, acc)
        zox_sys_o(Jump, jump)
        if (disableMovement->value || !jump->value) {
            continue;
        }
        float intended_vel = zox_jump_power;
        float acc_total = (intended_vel - vel->value.y) / delta_time;
        float acc_to_add = acc_total - acc->value.y;

        acc->value.y += acc_to_add;
        // zox_log("JUMPING");

        jump->value -= delta_time;
        if (jump->value < 0) {
            jump->value = 0;
        }
    }
} zoxd_system(Jump3AccSystem)
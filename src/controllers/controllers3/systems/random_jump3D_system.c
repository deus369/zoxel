void RandomJump3DSystem(ecs_iter_t *it) {
    const int random_jump_chance = 9988;
    zox_sys_begin()
    zox_sys_in(Grounded)
    zox_sys_out(Jump)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Grounded, grounded)
        zox_sys_o(Jump, jump)
        if (!grounded->value) continue;
        if (rand() % 10000 >= random_jump_chance) {
            jump->value = jump_timing;
        }
    } 
} zox_declare_system(RandomJump3DSystem)
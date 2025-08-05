void RandomJump3DSystem(ecs_iter_t *it) {
    const int random_jump_chance = 9988;
    zox_sys_begin()
    zox_sys_in(CanJump)
    zox_sys_out(JumpState)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CanJump, canJump)
        zox_sys_o(JumpState, jump)
        if (canJump->value) {
            if (rand() % 10000 >= random_jump_chance) {
                jump->value = zox_dirty_trigger;
            }
        }
    } 
} zox_declare_system(RandomJump3DSystem)
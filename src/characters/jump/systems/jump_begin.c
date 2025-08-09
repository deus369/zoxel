void JumpBeginSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(JumpState);
    zox_sys_out(Jump);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(JumpState, jumpState);
        zox_sys_o(Jump, jump);
        if (jumpState->value == zox_dirty_active) {
            // zox_log("Jump Begin Truly.");
            jump->value = jump_timing;
        }
    }
} zoxd_system(JumpBeginSystem)
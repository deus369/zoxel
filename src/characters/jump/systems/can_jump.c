void CanJumpSystem(ecs_iter_t *it) {
    byte can_jump_delay = 140 / 5;
    if (target_fps) {
        can_jump_delay = target_fps / 5;
    }
    zox_sys_begin()
    zox_sys_in(Grounded)
    zox_sys_out(CanJump)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Grounded, grounded)
        zox_sys_o(CanJump, canJump)
        if (grounded->value) {
            canJump->value = can_jump_delay;
        } else if (canJump->value && canJump->value != 255) {
            canJump->value--;
        }
    }
} zox_declare_system(CanJumpSystem)
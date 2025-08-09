#define jump_cooldown_state 251

void CanJumpSystem(ecs_iter_t *it) {
    byte can_jump_delay = 15;
    zox_sys_begin()
    zox_sys_in(Grounded)
    zox_sys_out(CanJump)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Grounded, grounded)
        zox_sys_o(CanJump, canJump)
        if (canJump->value >= jump_cooldown_state && canJump->value != 255) {
            canJump->value++;
        } else {
            if (grounded->value) {
                // zox_log("Can Jump");
                canJump->value = can_jump_delay;
            } else if (canJump->value && canJump->value != 255) {
                // zox_log("Can Still Jump: %i", canJump->value);
                canJump->value--;
            }
        }
    }
} zoxd_system(CanJumpSystem)
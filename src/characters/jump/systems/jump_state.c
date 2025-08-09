#define jump_cooldown_state 253
#define cooldown_start_landing 251

void CanJumpSystem(ecs_iter_t *it) {
    byte can_jump_delay = 15;
    zox_sys_begin()
    zox_sys_in(Grounded)
    zox_sys_in(JumpState)
    zox_sys_out(CanJump)
    zox_sys_out(LandState)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Grounded, grounded)
        zox_sys_i(JumpState, jump)
        zox_sys_o(CanJump, can_jump)
        zox_sys_o(LandState, landed)

        // Started to jump!
        if (jump->value) {
            can_jump->value = 0;
        }

        // Jump Cool Down
        /*else if (can_jump->value >= jump_cooldown_state && can_jump->value != 255) {
            can_jump->value++;
        }*/

        // If On Ground
        /*else if (grounded->value && !can_jump->value) {
            can_jump->value = 1;
            // Refresh our delay
            // can_jump->value = can_jump_delay;
        }*/

        can_jump->value = grounded->value;

        // Jumping! Some leeway for when you fall off a clip
        /*else if (can_jump->value && can_jump->value != 255) {
            can_jump->value--;
        }*/

        // assume this is when landed
        if (jump->value == zox_dirty_active) {
            landed->value = cooldown_start_landing;   // waiting
            // zox_log("JUMPED - landed [%i]", landed->value);
        }

        if (grounded->value) { // && can_jump->value && can_jump->value != 255) {
            if (landed->value == 255) {
                landed->value = zox_dirty_trigger;
                // zox_log("LANDED - landed [%i]", landed->value);
            } else if (landed->value > zox_dirty_end) {
                landed->value++;
            }
        }
    }
} zoxd_system(CanJumpSystem)
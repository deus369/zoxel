void RandomJump3DSystem(ecs_iter_t *it) {
    const int random_jump_chance = 9988;
    zox_field_in(Grounded, groundeds, 1)
    zox_field_out(Jump, jumps, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Grounded, groundeds, grounded)
        if (!grounded->value) continue;
        if (rand() % 10000 >= random_jump_chance) {
            zox_field_i_out(Jump, jumps, jump)
            jump->value = jump_timing;
        }
    } 
} zox_declare_system(RandomJump3DSystem)

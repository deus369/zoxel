const int random_jump_chance = 988;
void RandomJump3DSystem(ecs_iter_t *it) {
    #ifndef zoxel_has_random_jumping
        return;
    #endif
    const double jump_timing = 0.21;
    zox_field_out(Jump, jumps, 1)
    zox_field_out(Grounded, groundeds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Jump, jumps, jump)
        zox_field_i_in(Grounded, groundeds, grounded)
        if (grounded->value) {
            if (rand() % 1000 >= random_jump_chance) {
                Jump *jump = &jumps[i];
                jump->value = jump_timing;
            }
        }
    } 
} zox_declare_system(RandomJump3DSystem)

const int random_jump_chance = 988;
void RandomJump3DSystem(ecs_iter_t *it) {
    #ifndef zoxel_has_random_jumping
        return;
    #endif
    const double jump_timing = 0.21;
    Jump *jumps = ecs_field(it, Jump, 1);
    Grounded *groundeds = ecs_field(it, Grounded, 2);
    for (int i = 0; i < it->count; i++) {
        Jump *jump = &jumps[i];
        Grounded *grounded = &groundeds[i];
        if (grounded->value) {
            if (rand() % 1000 >= random_jump_chance) {
                Jump *jump = &jumps[i];
                jump->value = jump_timing;
                // grounded->value = 0;
            }
        }
    } 
} zox_declare_system(RandomJump3DSystem)

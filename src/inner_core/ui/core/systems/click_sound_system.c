void ClickSoundSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ClickState, clickStates, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ClickState, clickStates, clickState)
        if (!clickState->value) continue;
        double volume = 0.8 + 0.4 * (rand() % 101) / 100.0;
        spawn_generated_sound(world, note_frequencies[42], volume, instrument_violin);
    }
} zox_declare_system(ClickSoundSystem)

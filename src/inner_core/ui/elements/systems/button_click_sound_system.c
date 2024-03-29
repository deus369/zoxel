void ButtonClickSoundSystem(ecs_iter_t *it) {
    zox_iter_world()
    const ClickState *clickableStates = ecs_field(it, ClickState, 2);
    for (int i = 0; i < it->count; i++) {
        const ClickState *clickState = &clickableStates[i];
        if (!clickState->value) continue;
        double volume = 0.8 + 0.4 * (rand() % 101) / 100.0;
        spawn_generated_sound(world, note_frequencies[42], volume, instrument_violin);
    }
} zox_declare_system(ButtonClickSoundSystem)

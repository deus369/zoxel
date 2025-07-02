void ClickSoundSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ClickState, clickStates, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ClickState, clickStates, clickState)
        if (clickState->value != zox_click_state_clicked_this_frame) {
            continue;
        }
        const double volume = 0.53 + 0.32 * (rand() % 101) / 100.0;
        const double length = 0.33 + 0.22 * (rand() % 101) / 100.0;
        if (rand() % 100 >= 94) {
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[42], length, volume);
        } else {
            spawn_sound_generated(world, prefab_sound_generated, instrument_flute, note_frequencies[36], length, volume);
        }
    }
} zox_declare_system(ClickSoundSystem)
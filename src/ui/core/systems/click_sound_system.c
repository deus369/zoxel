void ClickSoundSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ClickState)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ClickState, clickState)
        if (clickState->value != zox_click_state_clicked_this_frame) {
            continue;
        }
        const double volume = (0.53 + 0.32 * (rand() % 101) / 100.0) * get_volume_sfx();
        const double length = 0.33 + 0.22 * (rand() % 101) / 100.0;
        if (rand() % 100 >= 94) {
            spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[38], length, volume);
        } else {
            const int frequency = (int)(22 + 8 * (rand() % 101) / 100.0);
            spawn_sound_generated(world, prefab_sound_generated, instrument_flute, note_frequencies[frequency], length, volume);
        }
    }
} zox_declare_system(ClickSoundSystem)
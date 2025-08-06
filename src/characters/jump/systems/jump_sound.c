void JumpSoundSystem(ecs_iter_t *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(JumpState);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(JumpState, jumpState);
        if (jumpState->value == zox_dirty_active) {
            const double volume = randf_range(0.74f, 1.1f) * get_volume_sfx();
            const double length = 0.11 + 0.09 * (rand() % 101) / 100.0;
            const byte frequency = 12 + rand() % 12;
            const byte instrument = rand() % 100 >= 94 ? instrument_piano : instrument_flute;
            spawn_sound_generated(world, prefab_sound_generated, instrument, note_frequencies[frequency], length, volume);
        }
    }
} zox_declare_system(JumpSoundSystem)
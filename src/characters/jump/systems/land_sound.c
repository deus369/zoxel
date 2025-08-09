void LandSoundSystem(ecs_iter_t *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(LandState);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(LandState, jumpState);
        if (jumpState->value == zox_dirty_active) {
            const double volume = randf_range(0.5f, 0.7f) * get_volume_sfx();
            const double length = randf_range(0.16f, 0.24f);
            const byte frequency = 12 + rand() % 6;
            const byte instrument = instrument_edm; // instrument_edm;
            spawn_sound_generated(
                world,
                prefab_sound_generated,
                instrument,
                note_frequencies[frequency],
                length,
                volume
            );
        }
    }
} zoxd_system(LandSoundSystem)
// TODO: Make a envelope setting for our generated sounds, jumps need to be sharper at start! WOOSH
void JumpSoundSystem(ecs_iter_t *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(JumpState);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(JumpState, jumpState);
        if (jumpState->value == zox_dirty_active) {
            const double volume = randf_range(0.84f, 1.3f) * get_volume_sfx();
            const double length = randf_range(0.18f, 0.34f);
            const byte frequency = 24 + rand() % 12;
            const byte instrument = instrument_edm;
            // rand() % 100 >= 94 ? instrument_piano : instrument_flute;
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
} zoxd_system(JumpSoundSystem)
// purely for detecting level up

// using level up state, we spawn sound and particles


void LevelUpSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UserLink)
    zox_sys_out(StatValue)
    zox_sys_out(ExperienceValue)
    zox_sys_out(ExperienceMax)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(UserLink, userLink)
        zox_sys_o(StatValue, statValue)
        zox_sys_o(ExperienceValue, experienceValue)
        zox_sys_o(ExperienceMax, experienceMax)
        if (experienceValue->value >= experienceMax->value) {
            experienceValue->value -= experienceMax->value;
            experienceMax->value = (int) ( experienceMax->value * experience_max_multiplier);
            statValue->value++;
            // zox_log_name(" + [%s] has leveled up", userLink->value)

            // level up sound
            spawn_sound_generated(world, prefab_sound_generated, instrument_piano, note_frequencies[32 + rand() % 4], 3.4, 1.4f * get_volume_sfx());

            // spawn particle system
            zox_muter(userLink->value, Children, children)
            const float3 bounds = zox_get_value(userLink->value, Bounds3D)
            const ecs_entity_t e2 = spawn_particle3D_emitter(world, userLink->value, 10, float3_scale(bounds, 3), (color) { 255, 255, 0, 55 });
            add_to_Children(children, e2);
            zox_set(e2, DestroyInTime, { 12 })
        }
    }
} zox_declare_system(LevelUpSystem)
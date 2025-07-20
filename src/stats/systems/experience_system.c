void ExperienceSystem(ecs_iter_t *it) {
    const float popup_spawn_y = 0.34f;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Dead)
    zox_sys_in(LastDamager)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Dead, dead)
        zox_sys_i(LastDamager, lastDamager)
        if (dead->value != zox_dirty_active) {
            continue;
        }
        if (zox_valid(lastDamager->value) && !zox_gett_value(lastDamager->value, Dead)) {
            // add experience to soul stat
            zox_geter(lastDamager->value, StatLinks, stats)
            if (stats->length < 2) {
                continue;
            }
            find_array_component_with_tag(stats, StatSoul, soul_stat)
            if (!soul_stat) {
                continue;
            }
            zox_muter(soul_stat, ExperienceValue, experience)
            float experience_gain = 2 + rand() % 6;
            experience->value += experience_gain;
            // zox_log(" + [%s] has gained [%f] xp", zox_get_name(lastDamager->value), experience_gain)


            const float3 bounds3D = zox_get_value(it->entities[i], Bounds3D)
            const float3 position = zox_get_value(it->entities[i], Position3D)
            const float3 popup_position = (float3) { position.x, position.y + bounds3D.y + popup_spawn_y, position.z };
            char popup_text[64];
            sprintf(popup_text, "+%i", (int) ceil(experience_gain));
            const color popup_color = (color) { 255, 255, 0, 255 };
            spawn_popup3_easy(world, popup_text, popup_color, popup_position, 5, 7 + rand() % 3);
        }
    }
} zox_declare_system(ExperienceSystem)

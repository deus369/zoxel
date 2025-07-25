// DotsSystem - skill applies damage to a users health
void DotsSystem(ecs_iter_t *it) {
    // const float damage_rate = 1.0f; // add this property to dot entity
    init_delta_time()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UserLink)
    zox_sys_in(SpawnerLink)
    zox_sys_in(SkillDamage)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(UserLink, userLink)
        zox_sys_i(SkillDamage, skillDamage)
        zox_sys_i(SpawnerLink, spawnerLink)
        if (!zox_valid(userLink->value) || zox_gett_value(userLink->value, Dead) || !skillDamage->value) {
            continue;
        }
        float damage = skillDamage->value;
        if (zox_valid(spawnerLink->value) && !zox_gett_value(spawnerLink->value, Dead)) {
            // todo: influence stat link for auras -> to determine strengthing stats
            zox_geter(spawnerLink->value, StatLinks, enemy_stats)
            int k = 0; // assuming intelligence is like 4th stat attribute for now
            for (int j = 0; j < enemy_stats->length; j++) {
                const ecs_entity_t stat = enemy_stats->value[j];
                if (zox_has(stat, StatAttribute)) {
                    k++;
                    if (k == 3) {
                        float value = zox_get_value(stat, StatValue)
                        damage += value;
                        break;
                    }
                }
            }
        }

        zox_geter(userLink->value, StatLinks, statLinks)
        // find health stat, maybe poison should target a stat type directly??
        find_array_component_with_tag(statLinks, HealthStat, health_stat)
        if (!health_stat) {
            zox_log(" ! user had no health\n")
            continue;
        }
        // const ecs_entity_t health_stat = statLinks->value[0];
        const float stat_value_max = zox_get_value(health_stat, StatValueMax)
        zox_get_muter(health_stat, StatValue, statValue)
        statValue->value += delta_time * skillDamage->value;
        if (statValue->value < 0) {
            statValue->value = 0;
        } else if (statValue->value > stat_value_max) {
            statValue->value = stat_value_max;
        }
        // rememer last to give xp - wait this tick rate - warlocks will always get xp lmao
        // zox_set(userLink->value, LastDamager, { spawnerLink->value })
        combat_on_hit(world, userLink->value,spawnerLink->value);
    }
} zox_declare_system(DotsSystem)
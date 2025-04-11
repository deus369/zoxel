// DotsSystem
void DotsSystem(ecs_iter_t *it) {
    // const float damage_rate = 1.0f; // add this property to dot entity
    init_delta_time()
    zox_field_world()
    zox_field_in(UserLink, userLinks, 1)
    zox_field_in(SpawnerLink, spawnerLinks, 2)
    zox_field_in(SkillDamage, skillDamages, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserLink, userLinks, userLink)
        if (!zox_alive(userLink->value)) continue;
        if (zox_gett_value(userLink->value, Dead)) continue;
        zox_field_i(SkillDamage, skillDamages, skillDamage)
        if (skillDamage->value == 0) continue;
        zox_field_i(SpawnerLink, spawnerLinks, spawnerLink)
        const StatLinks *statLinks = zox_get(userLink->value, StatLinks)
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
        if (statValue->value < 0) statValue->value = 0;
        else if (statValue->value > stat_value_max) statValue->value = stat_value_max;
        zox_set(userLink->value, LastDamager, { spawnerLink->value }) // rememer last to give xp
    }
} zox_declare_system(DotsSystem)
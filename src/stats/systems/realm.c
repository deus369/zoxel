void spawn_realm_stats(ecs_world_t *world, ecs_entity_t realm) {
    if (!zox_has(realm, StatLinks)) {
        zox_log("! realm does not have StatLinks [%lu]\n", realm)
        return;
    }
    // zox_get_muter(realm, StatLinks, stats)
    zox_geter(realm, StatLinks, oldStats)
    if (oldStats) {
        // clear previous
        for (int i = 0; i < oldStats->length; i++) {
            const ecs_entity_t stat = oldStats->value[i];
            if (zox_valid(stat)) {
                zox_delete(stat)
            }
        }
    }
    StatLinks stats = (StatLinks) { 0, NULL };
    initialize_StatLinks(&stats, 16);

    const float sat = 1.4f;
    const float dark = 0.4f;
    color_rgb soul_c = color_rgb_purple;
    color_rgb health_c = color_rgb_red;
    color_rgb energy_c = color_rgb_yellow;
    color_rgb mana_c = color_rgb_cyan;
    soul_c = color_rgb_darken(color_rgb_saturate(soul_c, sat), dark);
    health_c = color_rgb_darken(color_rgb_saturate(health_c, sat), dark);
    energy_c = color_rgb_darken(color_rgb_saturate(energy_c, sat), dark);
    mana_c = color_rgb_darken(color_rgb_saturate(mana_c, sat), dark);

    byte i = 0;
    // levels
    stats.value[i++] = spawn_realm_stat_level(world, "soul", "soul", soul_c);
    zox_add_tag(stats.value[i - 1], StatSoul);

    // states
    stats.value[i++] = spawn_realm_stat_state(world, "health", "health", health_c);
    zox_add_tag(stats.value[i - 1], HealthStat);
    stats.value[i++] = spawn_realm_stat_state(world, "energy", "energy", energy_c);
    stats.value[i++] = spawn_realm_stat_state(world, "mana", "mana", mana_c);
    // Regens
    stats.value[i++] = spawn_realm_stat_regen(world, "health regen", "healthregen");
    stats.value[i++] = spawn_realm_stat_regen(world, "energy regen", "energyregen");
    stats.value[i++] = spawn_realm_stat_regen(world, "mana regen", "manaregen");

    // Attributes
    stats.value[i++] = spawn_realm_stat_attribute(world, "strength", "strength");
    stats.value[i++] = spawn_realm_stat_attribute(world, "vitality", "vitality");
    stats.value[i++] = spawn_realm_stat_attribute(world, "endurance", "endurance");
    stats.value[i++] = spawn_realm_stat_attribute(world, "intelligence", "intelligence");
    stats.value[i++] = spawn_realm_stat_attribute(world, "wisdom", "wisdom");
    stats.value[i++] = spawn_realm_stat_attribute(world, "agility", "agility");
    stats.value[i++] = spawn_realm_stat_attribute(world, "dexterity", "dexterity");
    stats.value[i++] = spawn_realm_stat_attribute(world, "charm", "charm");
    stats.value[i++] = spawn_realm_stat_attribute(world, "luck", "luck");

    // Jobs
    // create regen stat
    // stats.value[i++] = spawn_realm_stat_level(world, "farming", "farming", color_rgb_gray);

    zox_set_ptr(realm, StatLinks, stats);
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [stats]\n")
#endif
}
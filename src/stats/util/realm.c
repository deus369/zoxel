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
    StatLinks *stats = &((StatLinks) { 0, NULL });
    resize_memory_component(StatLinks, stats, ecs_entity_t, 16)

    byte i = 0;
    // levels
    stats->value[i++] = spawn_realm_stat_level(world, "soul", "soul", color_rgb_purple);
    zox_add_tag(stats->value[i - 1], StatSoul)

    // states
    stats->value[i++] = spawn_realm_stat_state(world, "health", "health", color_rgb_red);
    zox_add_tag(stats->value[i - 1], HealthStat)
    stats->value[i++] = spawn_realm_stat_state(world, "energy", "energy", color_rgb_yellow);
    stats->value[i++] = spawn_realm_stat_state(world, "mana", "mana", color_rgb_cyan);
    // Regens
    stats->value[i++] = spawn_realm_stat_regen(world, "health regen", "healthregen");
    stats->value[i++] = spawn_realm_stat_regen(world, "energy regen", "energyregen");
    stats->value[i++] = spawn_realm_stat_regen(world, "mana regen", "manaregen");

    // Attributes
    stats->value[i++] = spawn_realm_stat_attribute(world, "strength", "strength");
    stats->value[i++] = spawn_realm_stat_attribute(world, "vitality", "vitality");
    stats->value[i++] = spawn_realm_stat_attribute(world, "endurance", "endurance");
    stats->value[i++] = spawn_realm_stat_attribute(world, "intelligence", "intelligence");
    stats->value[i++] = spawn_realm_stat_attribute(world, "wisdom", "wisdom");
    stats->value[i++] = spawn_realm_stat_attribute(world, "agility", "agility");
    stats->value[i++] = spawn_realm_stat_attribute(world, "dexterity", "dexterity");
    stats->value[i++] = spawn_realm_stat_attribute(world, "charm", "charm");
    stats->value[i++] = spawn_realm_stat_attribute(world, "luck", "luck");

    // Jobs
    // create regen stat
    // stats->value[i++] = spawn_realm_stat_level(world, "farming", "farming", color_rgb_gray);

    zox_set(realm, StatLinks, { stats->length, stats->value })
#ifdef zox_log_realm_generate
    zox_log(" + generated realm [stats]\n")
#endif
}
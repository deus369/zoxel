// shortcuts to realm stats for now
ecs_entity_t meta_stat_soul;
ecs_entity_t meta_stat_health;

ecs_entity_t create_stat_state(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name);
    zox_add_tag(e, StateStat)
    //zox_set(e, StatValue, { 10 })
    //zox_set(e, StatValueMax, { 10 })
    zox_prefab_set(e, StatValue, { 10 })
    zox_prefab_set(e, StatValueMax, { 10 })
    return e;
}

ecs_entity_t create_stat_level(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name);
    zox_add_tag(e, LevelStat)
    zox_prefab_set(e, StatValue, { 1 })
    zox_prefab_set(e, ExperienceValue, { 0 })
    zox_prefab_set(e, ExperienceMax, { 10 })
    return e;
}

ecs_entity_t create_stat_regen(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name);
    zox_add_tag(e, RegenStat)
    zox_prefab_set(e, StatValue, { 10 })
    // zox_prefab_set(e, StatValueMax, { 10 })
    return e;
}

ecs_entity_t create_stat_attribute(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name);
    zox_add_tag(e, AttributeStat)
    zox_prefab_set(e, StatValue, { 0 })
    // zox_prefab_set(e, StatValueMax, { 10 })
    return e;
}

// spawn prefabs for each meta stats
void create_game_stats(ecs_world_t *world, ecs_entity_t realm) {
    StatLinks *statLinks = zox_get_mut(realm, StatLinks)
    resize_memory_component(StatLinks, statLinks, ecs_entity_t, 16)
    statLinks->value[0] = create_stat_state(world, "health");
    statLinks->value[1] = create_stat_level(world, "soul");
    statLinks->value[2] = create_stat_state(world, "mana");
    statLinks->value[3] = create_stat_state(world, "energy");
    statLinks->value[4] = create_stat_regen(world, "health regen");
    statLinks->value[5] = create_stat_regen(world, "mana regen");
    statLinks->value[6] = create_stat_regen(world, "energy regen");
    statLinks->value[7] = create_stat_attribute(world, "strength");
    statLinks->value[8] = create_stat_attribute(world, "vitality");
    statLinks->value[9] = create_stat_attribute(world, "endurance");
    statLinks->value[10] = create_stat_attribute(world, "intelligence");
    statLinks->value[11] = create_stat_attribute(world, "wisdom");
    statLinks->value[12] = create_stat_attribute(world, "agility");
    statLinks->value[13] = create_stat_attribute(world, "dexterity");
    statLinks->value[14] = create_stat_attribute(world, "charm");
    statLinks->value[15] = create_stat_attribute(world, "luck");
    // create regen stat
    // statLinks->value[1] = create_stat_level(world, "farming");
    meta_stat_health = statLinks->value[0];
    meta_stat_soul = statLinks->value[1];
    zox_add_tag(meta_stat_health, HealthStat)
    zox_modified(realm, StatLinks)
}

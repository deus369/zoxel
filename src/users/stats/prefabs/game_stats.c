// shortcuts to realm stats for now
ecs_entity_t meta_stat_soul;
ecs_entity_t meta_stat_health;

ecs_entity_t create_stat_state(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name);
    zox_add_tag(e, StateStat)
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

// spawn prefabs for each meta stats
void create_game_stats(ecs_world_t *world, ecs_entity_t realm) {
    StatLinks *statLinks = zox_get_mut(realm, StatLinks)
    resize_memory_component(StatLinks, statLinks, ecs_entity_t, 2)
    statLinks->value[0] = create_stat_state(world, "health");
    meta_stat_health = statLinks->value[0];
    zox_add_tag(meta_stat_health, HealthStat)
    statLinks->value[1] = create_stat_level(world, "soul");
    meta_stat_soul = statLinks->value[1];
    zox_modified(realm, StatLinks)
}

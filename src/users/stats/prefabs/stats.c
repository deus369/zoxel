// shortcuts to realm stats for now
ecs_entity_t create_stat_state(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name, prefab_stat);
    zox_add_tag(e, StatState)
    zox_prefab_set(e, StatValue, { 10 })
    zox_prefab_set(e, StatValueMax, { 10 })
    return e;
}

ecs_entity_t create_stat_level(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name, prefab_stat);
    zox_add_tag(e, StatLevel)
    zox_prefab_set(e, StatValue, { 1 })
    zox_prefab_set(e, ExperienceValue, { 0 })
    zox_prefab_set(e, ExperienceMax, { 10 })
    return e;
}

ecs_entity_t create_stat_regen(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name, prefab_stat);
    zox_add_tag(e, StatRegen)
    zox_prefab_set(e, StatValue, { 10 })
    return e;
}

ecs_entity_t create_stat_attribute(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, name, prefab_stat);
    zox_add_tag(e, StatAttribute)
    zox_prefab_set(e, StatValue, { 0 })
    // zox_prefab_set(e, StatValueMax, { 10 })
    return e;
}

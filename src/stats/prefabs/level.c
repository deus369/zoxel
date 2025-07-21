ecs_entity_t create_stat_level(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, prefab_stat, name);
    zox_add_tag(e, StatLevel)
    zox_prefab_set(e, StatValue, { 1 })
    zox_prefab_set(e, ExperienceValue, { 0 })
    zox_prefab_set(e, ExperienceMax, { zox_experience_max_start })
    return e;
}
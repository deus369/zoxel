ecs_entity_t create_stat_state(ecs_world_t *world, const char *name) {
    ecs_entity_t e = spawn_meta_stat(world, prefab_stat, name);
    zox_add_tag(e, StatState)
    zox_prefab_set(e, StatValue, { 10 })
    zox_prefab_set(e, StatValueMax, { 10 })
    return e;
}
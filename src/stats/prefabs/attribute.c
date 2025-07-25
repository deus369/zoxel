ecs_entity_t create_stat_attribute(ecs_world_t *world,
    const char *name,
    const ecs_entity_t texture)
{
    ecs_entity_t e = spawn_meta_stat(world, prefab_stat, name);
    zox_add_tag(e, StatAttribute)
    zox_prefab_set(e, StatValue, { 0 })
    // zox_prefab_set(e, StatValueMax, { 10 })
    zox_prefab_set(e, TextureLink, { texture })
    return e;
}
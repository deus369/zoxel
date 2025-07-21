ecs_entity_t create_stat_regen(ecs_world_t *world,
    const char *name,
    const ecs_entity_t texture)
{
    ecs_entity_t e = spawn_meta_stat(world, prefab_stat, name);
    zox_add_tag(e, StatRegen)
    zox_prefab_set(e, StatValue, { 10 })
    zox_prefab_set(e, TextureLink, { texture })
    return e;
}
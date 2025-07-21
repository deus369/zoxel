ecs_entity_t create_stat_level(ecs_world_t *world,
    const char *name,
    const ecs_entity_t texture,
    const color_rgb c)
{
    ecs_entity_t e = spawn_meta_stat(world, prefab_stat, name);
    zox_add_tag(e, StatLevel)
    zox_prefab_set(e, StatValue, { 1 })
    zox_prefab_set(e, ExperienceValue, { 0 })
    zox_prefab_set(e, ExperienceMax, { zox_experience_max_start })
    zox_prefab_set(e, TextureLink, { texture })
    zox_prefab_set(e, ColorRGB, { c })
    return e;
}
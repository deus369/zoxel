ecs_entity_t spawn_skill_aura(ecs_world_t *world,
    const ecs_entity_t prefab,
    char* name,
    const float value,
    const float range,
    const color particle_color)
{
    const ecs_entity_t e = spawn_meta_skill(world, prefab, name);
    // zox_instance(prefab)
    zox_prefab_set(e, SkillDamage, { value })
    zox_prefab_set(e, SkillRange, { range })
    zox_prefab_set(e, Color, { particle_color })
    return e;
}

ecs_entity_t spawn_realm_skill_aura(ecs_world_t *world,
    char *name,
    const float value,
    const float range,
    const color particle_color,
    char *texture_name)
{
    const ecs_entity_t e = spawn_skill_aura(world,
        prefab_skill_aura,
        name,
        value,
        range,
        particle_color);
    zox_set(e, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data(texture_name)) })
    return e;
}

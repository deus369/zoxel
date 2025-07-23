ecs_entity_t spawn_skill_melee(ecs_world_t *world,
    const ecs_entity_t prefab,
    char* name,
    const float value,
    const float value_max,
    const float range,
    const ecs_entity_t resource,
    const float cost)
{
    const ecs_entity_t e = spawn_meta_skill(world, prefab, name);
    zox_set(e, SkillDamage, { value })
    zox_set(e, SkillDamageMax, { value_max })
    zox_set(e, SkillRange, { range })
    zox_set(e, SkillCost, { cost })
    zox_set(e, SkillResourceLink, { resource })
    return e;
}

ecs_entity_t spawn_realm_skill_melee(ecs_world_t *world,
    char* name,
    const float value,
    const float value_max,
    const float range,
    const ecs_entity_t resource,
    const float cost,
    char *texture_name)
{
    const ecs_entity_t e = spawn_skill_melee(world,
        prefab_skill_melee,
        name,
        value,
        value_max,
        range,
        resource,
        cost);
    zox_set(e, TextureLink, { string_hashmap_get(files_hashmap_textures, new_string_data(texture_name)) })
    return e;
}

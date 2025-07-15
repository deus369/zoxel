ecs_entity_t spawn_prefab_melee(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("melee")
    zox_add_tag(e, Melee)
    zox_prefab_set(e, SkillDamage, { 0 })
    zox_prefab_set(e, SkillRange, { 0 })
    zox_prefab_set(e, SkillCost, { 0 })
    zox_prefab_set(e, SkillActive, { 0 })
    return e;
}

ecs_entity_t spawn_skill_melee(ecs_world_t *world, const ecs_entity_t prefab, const char* name, const float value, const float range, const float cost) {
    const ecs_entity_t e = spawn_meta_skill(world, prefab, name);
    zox_prefab_set(e, SkillDamage, { value })
    zox_prefab_set(e, SkillRange, { range })
    zox_prefab_set(e, SkillCost, { cost })
    return e;
}
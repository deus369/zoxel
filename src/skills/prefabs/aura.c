ecs_entity_t spawn_prefab_aura(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("aura")
    zox_add_tag(e, Aura)
    zox_prefab_set(e, SkillDamage, { 0 })
    zox_prefab_set(e, SkillRange, { 0 })
    zox_prefab_set(e, SkillActive, { 0 })
    return e;
}

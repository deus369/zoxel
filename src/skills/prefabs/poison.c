ecs_entity_t spawn_prefab_poison(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_poison")
    zox_add_tag(e, Poison)
    zox_prefab_set(e, UserLink, { 0 })
    zox_prefab_set(e, SpawnerLink, { 0 })
    zox_prefab_set(e, SkillLink, { 0 })
    zox_prefab_set(e, SkillDamage, { 0 })
    return e;
}

ecs_entity_t spawn_poison(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t user, const ecs_entity_t spawner, const ecs_entity_t skill, const float damage) {
    zox_instance(prefab)
    zox_name("poison")
    // zox_log(" + set SpawnerLink to [%lu]\n", spawner)
    zox_set(e, UserLink, { user })          // user that owns poison debuff
    zox_set(e, SpawnerLink, { spawner })    // user that used skill
    zox_set(e, SkillLink, { skill })        // skill that created poison
    zox_set(e, SkillDamage, { damage })        // skill that created poison
    return e;
}

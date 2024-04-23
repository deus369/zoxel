ecs_entity_t prefab_skill;

ecs_entity_t spawn_prefab_skill(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_skill")
    zox_add_tag(e, Skill);
    // zox_add(e, ZoxName);
    prefab_skill = e;
    return e;
}

ecs_entity_t spawn_skill(ecs_world_t *world) {
    zox_instance(prefab_skill)
    zox_name("skill")
    // zox_set(e, Position3D, { position })
    return e;
}

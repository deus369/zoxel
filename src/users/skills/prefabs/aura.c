ecs_entity_t spawn_prefab_aura(ecs_world_t *world) {
    zox_prefab_child(prefab_skill)
    zox_prefab_name("prefab_aura")
    zox_add_tag(e, Aura);
    return e;
}

ecs_entity_t spawn_aura(ecs_world_t *world, const ecs_entity_t user) {
    zox_instance(prefab_aura)
    zox_name("aura")
    zox_set(e, UserLink, { user })
    return e;
}

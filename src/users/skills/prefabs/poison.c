ecs_entity_t prefab_poison;

ecs_entity_t spawn_prefab_poison(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_poison")
    zox_add_tag(e, Poison);
    zox_prefab_set(e, UserLink, { 0 })
    zox_prefab_set(e, SpawnerLink, { 0 })
    prefab_poison = e;
    return e;
}

ecs_entity_t spawn_poison(ecs_world_t *world, const ecs_entity_t user, const ecs_entity_t spawner) {
    zox_instance(prefab_poison)
    zox_name("poison")
    zox_set(e, UserLink, { user })
    zox_set(e, SpawnerLink, { spawner })
    return e;
}

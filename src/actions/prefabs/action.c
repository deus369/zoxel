ecs_entity_t prefab_action;

ecs_entity_t spawn_prefab_action(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("action")
    zox_add_tag(e, Action);
    prefab_skill = e;
    return e;
}

ecs_entity_t spawn_action(ecs_world_t *world) {
    zox_instance(prefab_action)
    zox_name("action")
    return e;
}
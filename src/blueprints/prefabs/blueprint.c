ecs_entity_t spawn_prefab_blueprint(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_prefab_name("blueprint")
    zox_add_tag(e, Blueprint)
    return e;
}

ecs_entity_t spawn_blueprint(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("blueprint")
    return e;
}


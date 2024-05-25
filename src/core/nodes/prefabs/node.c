ecs_entity_t spawn_prefab_node(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("node")
    zox_add_tag(e, Node)
    return e;
}

ecs_entity_t spawn_node(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("node")
    return e;
}

ecs_entity_t spawn_prefab_nodelink(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("nodelink")
    zox_add_tag(e, Nodelink)
    zox_prefab_add(e, NodeParent)
    zox_prefab_add(e, NodeNext)
    return e;
}

ecs_entity_t spawn_nodelink(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t e1, const ecs_entity_t e2) {
    zox_instance(prefab)
    zox_name("nodelink")
    zox_set(e, NodeParent, { e1 })
    zox_set(e, NodeNext, { e2 })
    return e;
}

ecs_entity_t spawn_prefab_nodegraph(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("nodegraph")
    zox_add_tag(e, Nodegraph)
    zox_prefab_add(e, Children)
    // zox_prefab_set(e, Children, { 0, NULL })
    return e;
}

ecs_entity_t spawn_nodegraph(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("nodegraph")
    return e;
}


ecs_entity_t spawn_prefab_bluenode(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_prefab_name("bluenode")
    zox_add_tag(e, Bluenode)
    return e;
}

ecs_entity_t spawn_bluenode(ecs_world_t *world, const ecs_entity_t prefab) {
    // const ecs_entity_t e = spawn_node(world, prefab, e1, e2);
    zox_instance(prefab)
    zox_name("bluenode")
    return e;
}

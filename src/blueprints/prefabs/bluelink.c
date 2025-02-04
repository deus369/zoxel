ecs_entity_t spawn_prefab_bluelink(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_prefab_name("bluelink")
    zox_add_tag(e, Bluelink)
    return e;
}

ecs_entity_t spawn_bluelink(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t e1, const ecs_entity_t e2) {
    const ecs_entity_t e = spawn_nodelink(world, prefab, e1, e2);
    zox_name("bluelink")
    return e;
}

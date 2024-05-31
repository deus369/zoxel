ecs_entity_t spawn_prefab_brain(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_brain")
    zox_add_tag(e, Brain)
    zox_prefab_add(e, BrainInputs)
    zox_prefab_add(e, BrainOutputs)
    zox_prefab_add(e, BrainLinks)
    zox_prefab_set(e, BrainDirty, { 0 })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_brain(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_instance(prefab)
    zox_name("brain")
    return e;
}

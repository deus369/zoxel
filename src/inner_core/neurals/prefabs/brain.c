ecs_entity_t prefab_brain;

ecs_entity_t spawn_prefab_brain(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_brain")
    zox_add_tag(e, Brain)
    zox_add(e, Children)
    zox_add(e, BrainInputs)
    zox_add(e, BrainOutputs)
    prefab_brain = e;
    return e;
}

ecs_entity_t spawn_brain(ecs_world_t *world) {
    zox_instance(prefab_brain)
    zox_name("brain")
    return e;
}

ecs_entity_t spawn_prefab_neuron(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_neuron")
    zox_add_tag(e, Neuron)
    zox_prefab_set(e, Signal, { 0 })
    zox_prefab_add(e, ParentLink)
    // this is only used for rendering / debugging
    zox_prefab_set(e, Position2D, { float2_zero })
    return e;
}

ecs_entity_t spawn_neuron(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t brain, const float2 position) {
    zox_instance(prefab)
    zox_name("neuron")
    zox_prefab_set(e, ParentLink, { brain })
    // zox_prefab_set(e, Weight, { weight })
    zox_prefab_set(e, Position2D, { position })
    return e;
}

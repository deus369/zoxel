ecs_entity_t prefab_neuron;

ecs_entity_t spawn_prefab_neuron(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_neuron")
    zox_add_tag(e, Neuron)
    zox_add(e, ParentLink)
    // zox_prefab_set(e, Weight, { 0 })
    // this is only used for rendering / debugging
    zox_prefab_set(e, Position2D, { float2_zero })
    zox_prefab_set(e, NeuronSignal, { 0 })
    prefab_neuron = e;
    return e;
}

ecs_entity_t spawn_neuron(ecs_world_t *world, const ecs_entity_t brain, const float2 position) {
    zox_instance(prefab_neuron)
    zox_name("neuron")
    zox_prefab_set(e, ParentLink, { brain })
    // zox_prefab_set(e, Weight, { weight })
    zox_prefab_set(e, Position2D, { position })
    return e;
}

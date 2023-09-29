ecs_entity_t prefab_neuron;

ecs_entity_t spawn_prefab_neuron(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_neuron")
    zox_add_tag(e, Neuron)
    zox_add(e, ParentLink)
    zox_prefab_set(e, Weight, { 0 })
    // this is only used for rendering / debugging
    zox_prefab_set(e, Position2D, { float2_zero })
    prefab_neuron = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab neuron [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_neuron(ecs_world_t *world, ecs_entity_t brain, float2 position, float weight) {
    zox_instance(prefab_neuron)
    zox_name("neuron")
    zox_prefab_set(e, ParentLink, { brain })
    zox_prefab_set(e, Weight, { weight })
    // convert this to render position
    const float y_position_mult = -2.0f / (float) (vertical_layers - 1); // -0.2f;
    const float x_position_mult = 1.0f / (float) (neurons_length - 1); // -0.2f;
    float2 render_position = position;
    render_position.x = render_position.x * x_position_mult;
    render_position.x *= 2.0f;
    render_position.x -= 1.0f;
    render_position.y = 1.0f + y_position_mult * render_position.y;
    zox_prefab_set(e, Position2D, { render_position })
    if (position.x == 0) { zox_add_tag(e, InputNeuron) }
    else if (position.x == 7) { zox_add_tag(e, OutputNeuron) }
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned neuron [%lu]\n", (long int) e);
    #endif
    return e;
}
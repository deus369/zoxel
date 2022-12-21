ecs_entity_t prefab_neuron;

ecs_entity_t spawn_prefab_neuron(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_neuron");
    set_unique_entity_name(world, e, "prefab_neuron");
    zoxel_add_tag(world, e, Neuron);
    zoxel_add(world, e, ParentLink);
    zoxel_set(world, e, Weight, { 0 });
    // this is only used for rendering / debugging
    zoxel_set(world, e, Position2D, { { 0, 0 } });
    ecs_defer_end(world);
    prefab_neuron = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log_arg("spawn_prefab neuron [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_neuron(ecs_world_t *world, ecs_entity_t brain, float2 position, float weight)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_neuron);
    set_unique_entity_name(world, e, "neuron");
    zoxel_set(world, e, ParentLink, { brain });
    zoxel_set(world, e, Weight, { weight });
    // convert this to render position
    const float y_position_mult = -2.0f / (float) (vertical_layers - 1); // -0.2f;
    const float x_position_mult = 1.0f / (float) (neurons_length - 1); // -0.2f;
    float2 render_position = position;
    render_position.x = render_position.x * x_position_mult;
    render_position.x *= 2.0f;
    render_position.x -= 1.0f;
    render_position.y = 1.0f + y_position_mult * render_position.y;
    zoxel_set(world, e, Position2D, { render_position });
    if (position.x == 0)
    {
        zoxel_add_tag(world, e, InputNeuron);
    }
    else if (position.x == 7)
    {
        zoxel_add_tag(world, e, OutputNeuron);
    }
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log_arg("Spawned neuron [%lu]\n", (long int) e);
    #endif
    return e;
}
ecs_entity_t prefab_brain;

ecs_entity_t spawn_prefab_brain(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_brain");
    set_unique_entity_name(world, e, "prefab_brain");
    zoxel_add_tag(world, e, Brain);
    zoxel_add(world, e, Children);
    ecs_defer_end(world);
    prefab_brain = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab brain [%lu].\n", (long int) (e));
    #endif
    return e;
}

extern ecs_entity_t spawn_neuron(ecs_world_t *world, ecs_entity_t brain, float2 position, float weight);
extern ecs_entity_t spawn_connection(ecs_world_t *world, ecs_entity_t neuronA, ecs_entity_t neuronB, float weight);

ecs_entity_t spawn_brain(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_brain);
    set_unique_entity_name(world, e, "brain");
    int connections_length = (neurons_length - 1); // neurons_length - 1;
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, (neurons_length + connections_length) * vertical_layers);
    int k = 0;
    for (int layer_count = 0; layer_count < vertical_layers; layer_count++)
    {
        int neuron_start_index = k;
        for (int i = 0; i < neurons_length; i++)
        {
            float2 position = (float2) { i, layer_count };
            children.value[k] = spawn_neuron(world, e, position, (rand() % 101) * 0.01f);
            k++;
        }
        for (int j = 0; j < connections_length; j++)
        {
            children.value[k] = spawn_connection(world,
                children.value[neuron_start_index + j],
                children.value[neuron_start_index + j + 1],
                (rand() % 101) * 0.01f);
            k++;
        }
    }
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned brain [%lu]\n", (long int) e);
    #endif
    return e;
}
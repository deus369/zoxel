extern ecs_entity_t spawn_neuron(ecs_world_t *world, ecs_entity_t brain, float2 position, float weight);
extern ecs_entity_t spawn_connection(ecs_world_t *world, ecs_entity_t neuronA, ecs_entity_t neuronB, float weight);
ecs_entity_t prefab_brain;

ecs_entity_t spawn_prefab_brain(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_brain")
    zox_add_tag(e, Brain)
    zox_add(e, Children)
    prefab_brain = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab brain [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_brain(ecs_world_t *world) {
    zox_instance(prefab_brain)
    zox_name("brain")
    int connections_length = (neurons_length - 1);
    int length = (neurons_length + connections_length) * vertical_layers;
    Children *children = ecs_get_mut(world, e, Children);
    resize_memory_component(Children, children, ecs_entity_t, length)
    int k = 0;
    for (int layer_count = 0; layer_count < vertical_layers; layer_count++) {
        int neuron_start_index = k;
        for (int i = 0; i < neurons_length; i++) {
            float2 position = (float2) { i, layer_count };
            children->value[k] = spawn_neuron(world, e, position, (rand() % 101) * 0.01f);
            k++;
        }
        for (int j = 0; j < connections_length; j++) {
            children->value[k] = spawn_connection(world, children->value[neuron_start_index + j],
                children->value[neuron_start_index + j + 1], (rand() % 101) * 0.01f);
            k++;
        }
    }
    ecs_modified(world, e, Children);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned brain [%lu]\n", (long int) e);
    #endif
    return e;
}
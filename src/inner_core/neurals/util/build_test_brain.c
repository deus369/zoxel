void build_brain_test(ecs_world_t *world, const ecs_entity_t e, const int neurons_length, const int vertical_layers) {
    int connections_length = (neurons_length - 1);
    int length = (neurons_length + connections_length) * vertical_layers;
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, length)
    BrainInputs *brain_inputs = zox_get_mut(e, BrainInputs)
    resize_memory_component(BrainInputs, brain_inputs, ecs_entity_t, vertical_layers)
    BrainOutputs *brain_outputs = zox_get_mut(e, BrainOutputs)
    resize_memory_component(BrainOutputs, brain_outputs, ecs_entity_t, vertical_layers)
    int k = 0; // total index for child
    for (int layer_count = 0; layer_count < vertical_layers; layer_count++) {
        int neuron_start_index = k;
        for (int i = 0; i < neurons_length; i++) {
            // const float weight = (rand() % 101) * 0.01f;
            float2 position = (float2) { i, layer_count };
            position = calculate_neuron_position(position, neurons_length, vertical_layers);
            const ecs_entity_t e2 = spawn_neuron(world, e, position);
            if (i == 0) {
                zox_add_tag(e2, InputNeuron)
                brain_inputs->value[layer_count] = e2;
            }
            else if (i == neurons_length - 1) {
                zox_add_tag(e2, OutputNeuron)
                zox_set(e2, NeuronSignal, { 0 })
                brain_outputs->value[layer_count] = e2;
            }
            children->value[k] = e2;
            k++;
        }
        for (int j = 0; j < connections_length; j++) {
            float weight = (rand() % 101) * 0.01f;
            // weight = (weight * 2.0f) - 1.0f;
            const ecs_entity_t a = children->value[neuron_start_index + j];
            const ecs_entity_t b = children->value[neuron_start_index + j + 1];
            const ecs_entity_t e2 = spawn_connection(world, a, b, weight);
            children->value[k] = e2;
            k++;
            // zox_log(" > weight [%i]: %f\n", j, weight)
        }
    }
    zox_modified(e, BrainInputs)
    zox_modified(e, BrainOutputs)
    zox_modified(e, Children)
}

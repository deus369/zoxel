float2 calculate_neuron_position(const float2 position, const int neurons_length, const int vertical_layers) {
    const float total_scale = neural_render_scale;
    // convert this to render position
    const float y_position_mult = -2.0f / (float) (vertical_layers - 1); // -0.2f;
    const float x_position_mult = 1.0f / (float) (neurons_length); // -0.2f;
    float2 render_position = position;
    render_position.x = render_position.x * x_position_mult;
    render_position.x *= 2.0f;
    render_position.x -= 1.0f;
    render_position.y = 1.0f + y_position_mult * render_position.y;
    render_position.x *= total_scale;
    render_position.y *= total_scale;
    return render_position;
}

// get all links going outt  of a neuron
// ecs_entity_t get_neuron_links_output() { }

// for any connecctions, if has neuron as a, start signals
unsigned char send_signals_from_neuron(ecs_world_t *world, const ecs_entity_t neuron, float signal) {
    zox_set(neuron, NeuronSignal, { signal })
    unsigned char has_outputs = 0;
    // finds connection link, should use the neurons connecction link here instead of scrolling through parent
    const ecs_entity_t brain = zox_get_value(neuron, ParentLink)
    const Children *children = zox_get(brain, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e2 = children->value[i];
        if (!zox_has(e2, Connection)) continue;
        const ConnectionData *connectionData = zox_get(e2, ConnectionData)
        if (connectionData->value.x == neuron) {
            zox_set(e2, Signal, { signal })
            // zox_log("set e2 [%lu] signal to 1\n", e2)
            has_outputs = 1;
        }
    }
    return has_outputs;
}

void feed_brain_random_input(ecs_world_t *world, const ecs_entity_t brain) {
    const BrainInputs *children = zox_get(brain, BrainInputs)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e2 = children->value[i];
        // if (!zox_has(e2, InputNeuron)) continue;
        float signal = (rand() % 101) * 0.01f;
        // signal *= brain_layers;
        // signal = (signal * 2.0f) - 1.0f;
        send_signals_from_neuron(world, e2, signal);
        // zox_log(" > input[%i]: %f\n", i, signal)
    }
}


void save_brain_as_texture(ecs_world_t *world, const ecs_entity_t brain) {
    int i2 = 0;
    color *colors = malloc(brain_texture_size.x * brain_texture_size.y * sizeof(color));
    const BrainOutputs *children = zox_get(brain, BrainOutputs)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e2 = children->value[i];
        // if (!zox_has(e2, OutputNeuron)) continue;
        const float output = zox_get_value(e2, NeuronSignal)
        const int output_2 = (int) (255 * output);
        colors[i2] = (color) { output_2, output_2, output_2, 255 };
        i2++;
    }
    save_texture_as_png(colors, brain_texture_size, "build/brain_test.png");
}

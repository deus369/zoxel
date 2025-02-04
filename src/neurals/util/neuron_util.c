// Sigmoid activation functionconst float signal_boost = 0.24f;

float sigmoid(float x) {
    return 1.0f / (1.0f + expf(- x));
}

// ReLU activation function
float relu(float x) {
    return fmaxf(0.0f, x);
}

// Define the derivative of the sigmoid activation function
float sigmoid_derivative(float x) {
    return sigmoid(x) * (1.0f - sigmoid(x));
}

float combine_signals(float x, float y) {
    return sigmoid(x * y);
    // return signal_boost + x * y;
}

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
unsigned char send_signals_from_neuron(ecs_world_t *world, const ecs_entity_t neuron, float value) {
    unsigned char has_outputs = 0;
    // finds connection link, should use the neurons connecction link here instead of scrolling through parent
    const ecs_entity_t brain = zox_get_value(neuron, ParentLink)
    const BrainLinks *brain_links = zox_get(brain, BrainLinks)
    for (int i = 0; i < brain_links->length; i++) {
        const ecs_entity_t e = brain_links->value[i];
        if (!zox_valid(e)) continue;
        const ConnectionData *connectionData = zox_get(e, ConnectionData)
        if (connectionData->value.x == neuron) {
            /*Signal *signal = zox_get_mut(e, Signal)
            signal->value = combine_signals(signal->value, value);
            zox_modified(e, Signal)*/
            zox_set(e, Signal, { value })
            has_outputs = 1;
        }
    }
    return has_outputs;
}

void reset_brain_values(ecs_world_t *world, const ecs_entity_t brain) {
    const Children *children = zox_get(brain, Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e = children->value[i];
        if (zox_has(e, InputNeuron)) continue;
        if (zox_has(e, Neuron)) zox_set(e, Signal, { 0 })
    }
}

void feed_brain_random_input(ecs_world_t *world, const ecs_entity_t brain) {
    reset_brain_values(world, brain);
    const BrainInputs *brain_inputs = zox_get(brain, BrainInputs)
    for (int i = 0; i < brain_inputs->length; i++) {
        const ecs_entity_t e = brain_inputs->value[i];
        float s = (rand() % 101) * 0.01f;
        zox_set(e, Signal, { s })
    }
}

void feed_brain_input(ecs_world_t *world, const ecs_entity_t brain, float input) {
    reset_brain_values(world, brain);
    const BrainInputs *brain_inputs = zox_get(brain, BrainInputs)
    for (int i = 0; i < brain_inputs->length; i++) {
        const ecs_entity_t e = brain_inputs->value[i];
        zox_set(e, Signal, { input })
    }
}


void randomize_brain_weights(ecs_world_t *world, const ecs_entity_t brain) {
    const BrainLinks *links = zox_get(brain, BrainLinks)
    for (int i = 0; i < links->length; i++) {
        const ecs_entity_t e = links->value[i];
        float w = (rand() % 101) * 0.01f;
        zox_set(e, Weight, { w })
    }
}

void save_brain_as_texture(ecs_world_t *world, const ecs_entity_t brain) {
    int i2 = 0;
    color *colors = malloc(brain_texture_size.x * brain_texture_size.y * sizeof(color));
    const BrainOutputs *children = zox_get(brain, BrainOutputs)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t e2 = children->value[i];
        // if (!zox_has(e2, OutputNeuron)) continue;
        const float output = zox_get_value(e2, Signal)
        const int output_2 = (int) (255 * output);
        colors[i2] = (color) { output_2, output_2, output_2, 255 };
        i2++;
    }
    save_texture_as_png(colors, brain_texture_size, "build/brain_test.png");
    free(colors);
}

ecs_entity_t spawn_brain_as_texture(ecs_world_t *world, const ecs_entity_t brain) {
    int i2 = 0;
    int colors_length = brain_texture_size.x * brain_texture_size.y;
    color *colors = malloc(colors_length * sizeof(color));
    const BrainOutputs *brain_outputs = zox_get(brain, BrainOutputs)
    for (int i = 0; i < brain_outputs->length; i++) {
        const ecs_entity_t e2 = brain_outputs->value[i];
        const float output = zox_get_value(e2, Signal)
        const int output_2 = (int) (255 * output);
        colors[i2] = (color) { output_2, output_2, output_2, 255 };
        i2++;
    }
    zox_new()
    zox_set(e, TextureData, { colors_length, colors })
    zox_set(e, TextureSize, { brain_texture_size })
    return e;
}

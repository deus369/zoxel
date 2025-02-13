//! Adds force to the velocity per frame.
void NeuronRenderSystem(ecs_iter_t *it) {
    if (zox_current_time < 0.1) return;
    const float line_thickness = 4.0f;
    init_delta_time()
    double animate_time = delta_time * 3;
    const float neuron_size = 0.1f;
    // const color_rgb neuron_color_input = (color_rgb) { 255, 0, 0 };
    // const color_rgb neuron_color_hidden = (color_rgb) { 0, 0, 255 };
    // const color_rgb neuron_color_output = (color_rgb) { 0, 255, 0 };
    zox_field_world()
    zox_field_in(Position2D, position2Ds, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(Position2D, position2Ds, position2D)
        float scale = neuron_size; //  * weight->value;
        if (zox_has(it->entities[i], InputNeuron)) scale *= 2.0f;
        float2 neuron_position = position2D->value;
        neuron_position.y += neural_position.y; // offset for world rendering
        const float output = zox_get_value(e, Signal)
        int gray_value = (int) (255 * output);
        spawn_line2D_square(world, neuron_position, (float2) { scale + scale * output, scale + scale * output }, line_thickness * 2, animate_time, (color_rgb) { gray_value, gray_value, gray_value });
    }
} zox_declare_system(NeuronRenderSystem)

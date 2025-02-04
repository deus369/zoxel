//! Adds force to the velocity per frame.
void ConnectionRenderSystem(ecs_iter_t *it) {
    if (zox_current_time < 0.1) return;
    init_delta_time()
    zox_iter_world()
    // const float signal_height = 0.02f * neural_render_scale;
    const float connection_thickness = 2 * neural_render_scale2;
    const float connection_min_thickness = 0.1f;
    const float neuron_size = 0.1f;
    double animate_time = delta_time * 3;
    // const float line_thickness2 = 2;
    color_rgb connected_line_color = (color_rgb) { 5, 155, 155 };
    // const float square_size = 0.02f;
    // const float neuron_min_size = 0.01f;
    zox_field_in(ConnectionData, connectionDatas, 1)
    zox_field_in(Weight, weights, 2)
    zox_field_in(Signal, signals, 3)
    zox_field_in(Transfer, transfers, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ConnectionData, connectionDatas, connectionData)
        const ecs_entity_t neuron_a = connectionData->value.x;
        if (!neuron_a) continue;
        const ecs_entity_t neuron_b = connectionData->value.y;
        if (!neuron_b) continue;
        zox_field_i(Weight, weights, weight)
        zox_field_i(Signal, signals, signal)
        int gray_value = (int) (255 * weight->value);
        color_rgb line_color = (color_rgb) { gray_value, gray_value, gray_value };
        float line_thickness = connection_min_thickness + (weight->value) * connection_thickness;
        if (signal->value) {
            line_color = connected_line_color;
            line_thickness *= 1.5f;
        }
        float2 neuron_a_position = zox_get_value(neuron_a, Position2D)
        neuron_a_position.y += neural_position.y; // offset for world rendering
        float2 neuron_b_position = zox_get_value(neuron_b, Position2D)
        neuron_b_position.y += neural_position.y; // offset for world rendering
        // draw connection line
        spawn_line2D_colored(world, neuron_a_position, neuron_b_position, line_thickness, animate_time, line_color);
        // draw signal point
        if (!signal->value) continue;
        zox_field_i(Transfer, transfers, transfer)
        // get signal position
        float2 signal_position = signal_position = float2_add(neuron_a_position, float2_multiply_float(float2_subtract(neuron_b_position, neuron_a_position), transfer->value));
        // spawn_line2D_colored(world, signal_position, float2_add(signal_position, (float2) { 0, signal_height + signal_height * 0.5f * signal->value }), line_thickness, animate_time, line_color);
        float scale = neuron_size * neural_render_scale2;
        const float output = signal->value;
        int gray_value2 = (int) (255 * signal->value);
        spawn_line2D_square(world, signal_position, (float2) { scale * output, scale * output }, connection_thickness, animate_time, (color_rgb) { gray_value2, gray_value2, gray_value2 });
        // spawn_line2D_square(world, signal_position, (float2) { square_size, square_size }, 0.5f, animate_time);
        // zox_log(" + transfer->value [%f] at pos [%f]\n", transfer->value, signal_position.x)
    }
} zox_declare_system(ConnectionRenderSystem)

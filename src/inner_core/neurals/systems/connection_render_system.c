//! Adds force to the velocity per frame.
void ConnectionRenderSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    double deltaTime = (double) it->delta_time;
    float animate_time = deltaTime * 0.5f;
    // const float y_position = -0.8f;
    const float square_size = 0.02f;
    const ConnectionData *connectionDatas = ecs_field(it, ConnectionData, 2);
    const Weight *weights = ecs_field(it, Weight, 3);
    const Signal *signals = ecs_field(it, Signal, 4);
    const SignalStrength *signalStrengths = ecs_field(it, SignalStrength, 5);
    for (int i = 0; i < it->count; i++)
    {
        const ConnectionData *connectionData = &connectionDatas[i];
        ecs_entity_t neuron_a = connectionData->value.x;
        ecs_entity_t neuron_b = connectionData->value.y;
        if (neuron_a != 0 && neuron_b != 0)
        {
            const Weight *weight = &weights[i];
            float2 neuron_a_position = ecs_get(world, neuron_a, Position2D)->value;
            float2 neuron_b_position = ecs_get(world, neuron_b, Position2D)->value;
            spawn_line2D(world, neuron_a_position, neuron_b_position,
                0.2f + weight->value * 6.0f, animate_time);
            const Signal *signal = &signals[i];
            if (signal->value == 1)
            {
                const SignalStrength *signalStrength = &signalStrengths[i];
                // get signal position
                float2 signal_position = neuron_a_position;
                signal_position = float2_add(signal_position, float2_multiply_float(
                    float2_subtract(neuron_b_position, neuron_a_position),
                    signalStrength->value));
                spawn_line2D_square(world,
                    signal_position, // (float2) { neuron_a_position.x + (x_position2 - x_position) * signalStrength->value, y_position },
                    (float2) { square_size, square_size }, 0.5f, animate_time);
            }
            // printf("    [%i]    Position3D %f -> %f = [%f]\n", i, x_position, x_position2, signal->value);
        }
    }
}
zox_declare_system(ConnectionRenderSystem)
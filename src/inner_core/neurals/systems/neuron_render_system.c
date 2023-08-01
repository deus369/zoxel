//! Adds force to the velocity per frame.
void NeuronRenderSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    float aspect_ratio = screen_dimensions.x / (float) screen_dimensions.y;
    ecs_world_t *world = it->world;
    // double delta_time = (double) it->delta_time;
    float animate_time = delta_time * 0.5f;
    // const float y_position = 1.0f;
    // const float y_position_mult = -2.0f / (float) (vertical_layers - 1); // -0.2f;
    const float neuron_min_size = 0.01f;
    const float neuron_size = 0.06f;
    const Weight *weights = ecs_field(it, Weight, 2);
    const Position2D *position2Ds = ecs_field(it, Position2D, 3);
    for (int i = 0; i < it->count; i++) {
        const Weight *weight = &weights[i];
        const Position2D *position2D = &position2Ds[i];
        float scaleA = 2.5f;
        if (ecs_has(world, it->entities[i], InputNeuron)) {
            scaleA = 10.0f;
        }
        spawn_line2D_square(world,  position2D->value, // (float2) { x_position, y_position + y_position_mult * position2D->value.y },
            (float2) { (neuron_min_size + neuron_size * weight->value) / aspect_ratio, neuron_min_size + neuron_size * weight->value },
            scaleA, animate_time);
        // printf("    [%i]    Position3D %f -> %f = [%f]\n", i, x_position, x_position2, signal->value);
    }
}
zox_declare_system(NeuronRenderSystem)
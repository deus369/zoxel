void NeuronFeedForwardSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_out(Signal, signals, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(Signal, signals, signal)
        if (signal->value == 0) continue; // only progress if signal is enabled
        zox_field_e()
        if (send_signals_from_neuron(world, e, signal->value)) {
#ifdef zox_log_neurals
            zox_log(" + s from n [%f]\n", signal->value)
#endif
            signal->value = 0;
        }
    }
} zoxd_system(NeuronFeedForwardSystem)

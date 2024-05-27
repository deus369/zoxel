void LinkFeedForwardSystem(ecs_iter_t *it) {
    if (zox_current_time < neural_brain_delay) return;
    float total_loss = 0.0f;
    float total_loss_gradient = 0.0f;
    float target_output = 0.7f; // Assuming your target output is 0.7
    float learning_rate = 0.01f; // Assuming your learning rate is 0.01
    init_delta_time()
    zox_iter_world()
    zox_field_in(ConnectionData, connectionDatas, 1)
    zox_field_in(BrainLink, brainLinks, 2)
    zox_field_out(Weight, weights, 3)
    zox_field_out(Signal, signals, 4)
    zox_field_out(Transfer, transfers, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(Signal, signals, signal)
        if (signal->value == 0) continue; // only progress if signal is enabled
        zox_field_i(ConnectionData, connectionDatas, connectionData)
        zox_field_o(Transfer, transfers, transfer)
        transfer->value += delta_time * neural_process_speed;
        if (transfer->value < 1.0f) continue;
        transfer->value = 0;
        unsigned char reached_end = 0;
        zox_field_o(Weight, weights, weight)
        const ecs_entity_t neuron_b = connectionData->value.y;
        if (neuron_b) {
            // const float weighted_signal = sigmoid((signal->value + 0.1f) * weight->value);
            const float weighted_signal = signal->value * weight->value;
            Signal *neuron_signal = zox_get_mut(neuron_b, Signal)
            neuron_signal->value += weighted_signal;
            zox_modified(neuron_b, Signal)
            if (zox_has(neuron_b, OutputNeuron)) reached_end = 1;
#ifdef zox_log_neurals
            zox_log(" + s [%f] > w [%f] > ws [%f] > n [%f]\n", signal->value, weight->value, weighted_signal, neuron_signal->value)
#endif
        }
        signal->value = 0;
        if (reached_end) {
            zox_field_i(BrainLink, brainLinks, brainLink)
            zox_set(brainLink->value, BrainDirty, { 1 })
        }
    }
} zox_declare_system(LinkFeedForwardSystem)

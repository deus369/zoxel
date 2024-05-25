
// Sigmoid activation function
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

void FeedForwardSystem(ecs_iter_t *it) {
    if (zox_current_time < neural_brain_delay) return;
    float total_loss = 0.0f;
    float total_loss_gradient = 0.0f;
    float target_output = 0.7f; // Assuming your target output is 0.7
    float learning_rate = 0.01f; // Assuming your learning rate is 0.01

    init_delta_time()
    zox_iter_world()
    zox_field_in(ConnectionData, connectionDatas, 1)
    zox_field_out(Weight, weights, 2)
    zox_field_out(Signal, signals, 3)
    zox_field_out(Transfer, transfers, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(Signal, signals, signal)
        if (signal->value == 0) continue; // only progress if signal is enabled
        zox_field_i(ConnectionData, connectionDatas, connectionData)
        zox_field_o(Transfer, transfers, transfer)
        transfer->value += delta_time * neural_process_speed;
        if (transfer->value >= 1.0f) {
            zox_field_o(Weight, weights, weight)
            const ecs_entity_t neuron_b = connectionData->value.y;
            if (neuron_b) {
                const float weighted_signal = signal->value * weight->value;
                const float send_signal = 0.5f + (weighted_signal); // activate function
                // const float send_signal = (signal->value + weight->value) / 2; // sigmoid(weighted_signal); // activate function
                if (!send_signals_from_neuron(world, neuron_b, send_signal)) {
                    // zox_set(neuron_b, NeuronSignal, { send_signal })
                    // zox_log(" > output[%i]: %f\n", i, send_signal)
                }

                // Perform backpropagation
                // Assuming you have access to the target output (e.g., target_output) and the predicted output (send_signal)
                /*const float loss = 0.5f * powf(target_output - send_signal, 2); // Calculate the loss
                const float loss_gradient = -(target_output - send_signal); // Compute the gradient of the loss with respect to the output
                const float weighted_signal_gradient = loss_gradient * sigmoid_derivative(weighted_signal); // Compute the gradient of the loss with respect to the weighted signal
                const float signal_gradient = weighted_signal_gradient * signal->value; // Compute the gradient of the loss with respect to the input signal
                const float weight_gradient = weighted_signal_gradient * signal->value; // Compute the gradient of the loss with respect to the weight
                // Update the weight using gradient descent or its variant (e.g., assuming a constant learning rate)
                weight->value -= learning_rate * weight_gradient;
                // Accumulate the total loss for monitoring
                total_loss += loss;
                total_loss_gradient += loss_gradient;*/
            }
            transfer->value = 0;
            signal->value = 0;
        }
    }
} zox_declare_system(FeedForwardSystem)

// increase connected weight
/*const float neuron_weight = zox_get_value(connectionData->value.y, Weight)
float new_weight = neuron_weight + weight->value * add_multiplier;
if (new_weight > 1.0f) new_weight = 1; // -= 1.0f;
zox_set(neuron_b, Weight, { new_weight })*/
// zox_set(neuron_b, Signal, { 1 })
// zox_log("signal strength increased at %i\n", i)

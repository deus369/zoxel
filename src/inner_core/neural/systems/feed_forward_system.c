//! Get all connections belonging to a neuron. Then begin the signals.
void neuron_signal_begin(ecs_world_t *world, ecs_entity_t e)
{
    ecs_entity_t brain_entity = ecs_get(world, e, ParentLink)->value;
    const Children *children = ecs_get(world, brain_entity, Children);
    // for all children, if connection..
    for (int i = 0; i < children->length; i++)
    {
        ecs_entity_t connection_entity = children->value[i];
        if (ecs_has(world, connection_entity, Connection))
        {
            const ConnectionData *connectionData = ecs_get(world, connection_entity, ConnectionData);
            if (connectionData->value.x == e)
            {
                ecs_set(world, connection_entity, Signal, { 1 });
            }
        }
    }
}

//! Adds force to the velocity per frame.
void FeedForwardSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    double deltaTime = (double) it->delta_time;
    const float brain_speed = 4.0f;
    const float add_multiplier = 0.1f;
    const ConnectionData *connectionDatas = ecs_field(it, ConnectionData, 2);
    const Weight *weights = ecs_field(it, Weight, 3);
    Signal *signals = ecs_field(it, Signal, 4);
    SignalStrength *signalStrengths = ecs_field(it, SignalStrength, 5);
    for (int i = 0; i < it->count; i++)
    {
        const ConnectionData *connectionData = &connectionDatas[i];
        Signal *signal = &signals[i];
        if (signal->value != 1)
        {
            if (ecs_has(world, connectionData->value.x, InputNeuron))
            {
                neuron_signal_begin(world, connectionData->value.x);
            }
            continue;
        }
        SignalStrength *signalStrength = &signalStrengths[i];
        // from x to y
        signalStrength->value += deltaTime * brain_speed;
        if (signalStrength->value >= 1.0f)
        {
            const Weight *weight = &weights[i];
            // increase weight of neuron b
            // signalStrength->value -= 1.0f;
            signalStrength->value = 0;
            signal->value = 0;
            if (connectionData->value.y != 0)
            {
                neuron_signal_begin(world, connectionData->value.y);
                const Weight *neuron_weight = ecs_get(world, connectionData->value.y, Weight);
                float new_weight = neuron_weight->value + weight->value * add_multiplier;
                if (new_weight > 1.0f)
                {
                    new_weight -= 1.0f;
                }
                ecs_set(world, connectionData->value.y, Weight, { new_weight });
            }
        }
    }
}
zoxel_declare_system(FeedForwardSystem)
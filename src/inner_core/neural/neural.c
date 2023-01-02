#ifndef zoxel_neural
#define zoxel_neural

const int neurons_length = 12;
const int vertical_layers = 12;
// tags per entity
ECS_DECLARE(Brain);
ECS_DECLARE(Neuron);
ECS_DECLARE(Connection);
ECS_DECLARE(InputNeuron);
ECS_DECLARE(OutputNeuron);
// components
//! The weight of the neural connection
zoxel_component(Weight, float);
//! If the signal is sending
zoxel_state_component(Signal);
//! The signal value of a connection
zoxel_component(SignalStrength, float);
//! The weight of the neural connection
zoxel_component(ConnectionData, ecs_entity_2);
//! A brain holds an array of connections.
// zoxel_memory_component(Connections, ecs_entity_t);
// prefabs
#include "prefabs/brain.c"
#include "prefabs/neuron.c"
#include "prefabs/connection.c"
// systems
#include "systems/feed_forward_system.c"
#include "systems/connection_render_system.c"
#include "systems/neuron_render_system.c"

void NeuralImport(ecs_world_t *world)
{
    zoxel_module(Neural)
    ECS_TAG_DEFINE(world, Brain);
    ECS_TAG_DEFINE(world, Neuron);
    ECS_TAG_DEFINE(world, Connection);
    ECS_TAG_DEFINE(world, InputNeuron);
    ECS_TAG_DEFINE(world, OutputNeuron);
    ECS_COMPONENT_DEFINE(world, Weight);
    ECS_COMPONENT_DEFINE(world, Signal);
    ECS_COMPONENT_DEFINE(world, SignalStrength);
    ECS_COMPONENT_DEFINE(world, ConnectionData);
    // zoxel_memory_component_define(world, ECS_COMPONENT_DEFINE);
    // zoxel_memory_component_define(world, Connections);
    // prefabs
    spawn_prefab_brain(world);
    spawn_prefab_neuron(world);
    spawn_prefab_connection(world);
    // systems
    zoxel_system(world, FeedForwardSystem, EcsOnUpdate, [none] Connection, [in] ConnectionData, [in] Weight, [out] Signal, [out] SignalStrength);
    zoxel_system(world, ConnectionRenderSystem, EcsOnUpdate,
        [none] Connection, [in] ConnectionData, [in] Weight, [in] Signal, [in] SignalStrength);
    zoxel_system(world, NeuronRenderSystem, EcsOnUpdate,
        [none] Neuron, [in] Weight, [in] Position2D);
    // Spawn brain
    #ifdef zoxel_test_brain
    spawn_brain(world);
    #endif
}
#endif
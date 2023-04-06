#ifndef zoxel_neural
#define zoxel_neural

const int neurons_length = 12;
const int vertical_layers = 12;
zoxel_declare_tag(Brain)
zoxel_declare_tag(Neuron)
zoxel_declare_tag(Connection)
zoxel_declare_tag(InputNeuron)
zoxel_declare_tag(OutputNeuron)
zoxel_component(Weight, float)                  //! The weight of the neural connection
zoxel_byte_component(Signal)                   //! If the signal is sending
zoxel_component(SignalStrength, float)          //! The signal value of a connection
zoxel_component(ConnectionData, ecs_entity_2)   //! The weight of the neural connection
// zoxel_memory_component(Connections, ecs_entity_t);   //! A brain holds an array of connections.
#include "prefabs/brain.c"
#include "prefabs/neuron.c"
#include "prefabs/connection.c"
#include "systems/feed_forward_system.c"
#include "systems/connection_render_system.c"
#include "systems/neuron_render_system.c"

zoxel_begin_module(Neurals)
zoxel_define_tag(Brain)
zoxel_define_tag(Neuron)
zoxel_define_tag(Connection)
zoxel_define_tag(InputNeuron)
zoxel_define_tag(OutputNeuron)
zoxel_define_component(Weight)
zoxel_define_component(Signal)
zoxel_define_component(SignalStrength)
zoxel_define_component(ConnectionData)
zoxel_system(FeedForwardSystem, EcsOnUpdate, [none] Connection, [in] ConnectionData, [in] Weight, [out] Signal, [out] SignalStrength)
zoxel_system(ConnectionRenderSystem, EcsOnUpdate, [none] Connection, [in] ConnectionData, [in] Weight, [in] Signal, [in] SignalStrength)
zoxel_system(NeuronRenderSystem, EcsOnUpdate, [none] Neuron, [in] Weight, [in] Position2D)
spawn_prefab_brain(world);
spawn_prefab_neuron(world);
spawn_prefab_connection(world);
#ifdef zoxel_test_brain
spawn_brain(world);
#endif
zoxel_end_module(Neurals)

#endif
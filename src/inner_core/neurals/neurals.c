#ifndef zox_neural
#define zox_neural

const int neurons_length = 12;
const int vertical_layers = 12;
zox_declare_tag(Brain)
zox_declare_tag(Neuron)
zox_declare_tag(Connection)
zox_declare_tag(InputNeuron)
zox_declare_tag(OutputNeuron)
zox_component_float(Weight)                  //! The weight of the neural connection
zox_component_byte(Signal)                   //! If the signal is sending
zox_component_float(SignalStrength)          //! The signal value of a connection
zox_component(ConnectionData, ecs_entity_2)   //! The weight of the neural connection
#include "prefabs/brain.c"
#include "prefabs/neuron.c"
#include "prefabs/connection.c"
#include "systems/feed_forward_system.c"
#include "systems/connection_render_system.c"
#include "systems/neuron_render_system.c"

void spawn_prefabs_neurals(ecs_world_t *world) {
    spawn_prefab_brain(world);
    spawn_prefab_neuron(world);
    spawn_prefab_connection(world);
#ifdef zoxel_test_brain
    spawn_brain(world);
#endif
}

zox_begin_module(Neurals)
zox_define_tag(Brain)
zox_define_tag(Neuron)
zox_define_tag(Connection)
zox_define_tag(InputNeuron)
zox_define_tag(OutputNeuron)
zox_define_component_float(Weight)
zox_define_component_byte(Signal)
zox_define_component_float(SignalStrength)
zox_define_component(ConnectionData)
zox_system(FeedForwardSystem, EcsOnUpdate, [none] Connection, [in] ConnectionData, [in] Weight, [out] Signal, [out] SignalStrength)
zox_system(ConnectionRenderSystem, EcsOnUpdate, [none] Connection, [in] ConnectionData, [in] Weight, [in] Signal, [in] SignalStrength)
zox_system(NeuronRenderSystem, EcsOnUpdate, [none] Neuron, [in] Weight, [in] Position2D)
zoxel_end_module(Neurals)

#endif

#if !defined(zox_mod_neurals) && defined(zox_mod_nodes)
#define zox_mod_neurals

zox_declare_tag(Brain)
zox_declare_tag(Neuron)
zox_declare_tag(Connection)
zox_declare_tag(InputNeuron)
zox_declare_tag(OutputNeuron)
zox_component_float(Weight)                     //! The weight of the neural connection
zox_component_float(Signal)                     //! If the signal is sending
zox_component_float(Transfer)                   //! The signal value of a connection
zox_component(ConnectionData, ecs_entity_2)     //! The weight of the neural connection
zox_component_byte(BrainDirty)
zox_component_entity(BrainLink)
zox_memory_component(BrainInputs, ecs_entity_t)
zox_memory_component(BrainOutputs, ecs_entity_t)
zox_memory_component(BrainLinks, ecs_entity_t)
#include "data/settings.c"
#include "prefabs/prefabs.c"
#include "util/neuron_util.c"
#include "util/build_test_brain.c"
#include "systems/input_neuron_system.c"
#include "systems/feed_forward_system.c"
#include "systems/neuron_feed_forward_system.c"
#include "systems/connection_render_system.c"
#include "systems/neuron_render_system.c"

zox_begin_module(Neurals)
zox_define_tag(Brain)
zox_define_tag(Neuron)
zox_define_tag(Connection)
zox_define_tag(InputNeuron)
zox_define_tag(OutputNeuron)
zox_define_component_float(Weight)
zox_define_component_float(Signal)
zox_define_component_float(Transfer)
zox_define_component(ConnectionData)
zox_define_component_byte(BrainDirty)
zox_define_component_entity(BrainLink)
zox_define_memory_component(BrainInputs)
zox_define_memory_component(BrainOutputs)
zox_define_memory_component(BrainLinks)
zox_system(NeuronInputSystem, EcsOnUpdate, [none] InputNeuron) //  [out] Transfer,
zox_system(LinkFeedForwardSystem, EcsPostUpdate, [in] ConnectionData, [out] Weight, [out] Signal, [out] Transfer, [none] Connection)
zox_system(NeuronFeedForwardSystem, EcsOnUpdate, [out] Signal, [none] Neuron, [none] !OutputNeuron)

#ifdef zox_render_brain
zox_system_1(NeuronRenderSystem, zox_pip_mainthread, [in] Position2D, [none] Neuron)
zox_system_1(ConnectionRenderSystem, zox_pip_mainthread, [in] ConnectionData, [in] Weight, [in] Signal, [in] Transfer, [none] Connection)
#endif
spawn_prefabs_neurals(world);
#ifdef zox_test_brain
spawn_test_brain(world);
#endif
zoxel_end_module(Neurals)

#endif

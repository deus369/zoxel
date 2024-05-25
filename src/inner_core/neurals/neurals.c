#if !defined(zox_mod_neurals) && defined(zox_mod_nodes)
#define zox_mod_neurals

// #define zox_test_brain
// #define zox_render_brain
const float neural_process_speed = 8.0f;
const int brain_layers = 16;
const int2 brain_texture_size = (int2) { 4, 4 };
const float neural_render_scale = 8.0f;
const float neural_render_scale2 = 2.0f; // thickneess
const double neural_brain_delay = 0;
ecs_entity_t local_brain = 0;
zox_declare_tag(Brain)
zox_declare_tag(Neuron)
zox_declare_tag(Connection)
zox_declare_tag(InputNeuron)
zox_declare_tag(OutputNeuron)
zox_component_float(Weight)                     //! The weight of the neural connection
zox_component_float(Signal)                     //! If the signal is sending
zox_component_float(Transfer)                   //! The signal value of a connection
zox_component_float(NeuronSignal)               //! The signal value of a connection
zox_component(ConnectionData, ecs_entity_2)     //! The weight of the neural connection
zox_memory_component(BrainInputs, ecs_entity_t)
zox_memory_component(BrainOutputs, ecs_entity_t)
#include "prefabs/brain.c"
#include "prefabs/neuron.c"
#include "prefabs/connection.c"
#include "util/neuron_util.c"
#include "util/build_test_brain.c"
#include "systems/input_neuron_system.c"
#include "systems/feed_forward_system.c"
#include "systems/connection_render_system.c"
#include "systems/neuron_render_system.c"

void spawn_prefabs_neurals(ecs_world_t *world) {
    spawn_prefab_brain(world);
    spawn_prefab_neuron(world);
    spawn_prefab_connection(world);
#ifdef zox_test_brain
    const ecs_entity_t brain = spawn_brain(world);
    build_brain_test(world, brain, brain_layers, brain_texture_size.x * brain_texture_size.y);
    local_brain = brain;
#endif
}

zox_begin_module(Neurals)
zox_define_tag(Brain)
zox_define_tag(Neuron)
zox_define_tag(Connection)
zox_define_tag(InputNeuron)
zox_define_tag(OutputNeuron)
zox_define_component_float(Weight)
zox_define_component_float(Signal)
zox_define_component_float(Transfer)
zox_define_component_float(NeuronSignal)
zox_define_component(ConnectionData)
zox_define_memory_component(BrainInputs)
zox_define_memory_component(BrainOutputs)
zox_system(NeuronInputSystem, EcsOnUpdate, [none] InputNeuron) //  [out] Transfer,
zox_system(FeedForwardSystem, EcsOnUpdate, [in] ConnectionData, [out] Weight, [out] Signal, [out] Transfer, [none] Connection)
#ifdef zox_render_brain
zox_system_1(NeuronRenderSystem, zox_pip_mainthread, [in] Position2D, [none] Neuron)
zox_system_1(ConnectionRenderSystem, zox_pip_mainthread, [in] ConnectionData, [in] Weight, [in] Signal, [in] Transfer, [none] Connection)
#endif
spawn_prefabs_neurals(world);
zoxel_end_module(Neurals)

#endif

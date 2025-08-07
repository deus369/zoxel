#if !defined(zoxm_neurals) && defined(zoxm_nodes)
#define zoxm_neurals

zox_declare_tag(Brain)
zox_declare_tag(Neuron)
zox_declare_tag(Connection)
zox_declare_tag(InputNeuron)
zox_declare_tag(OutputNeuron)
zox_component_float(Weight)                     //! The weight of the neural connection
zox_component_float(Signal)                     //! If the signal is sending
zox_component_float(Transfer)                   //! The signal value of a connection
zox_component(ConnectionData, entity2)     //! The weight of the neural connection
zox_component_byte(BrainDirty)
zox_component_entity(BrainLink)
zox_memory_component(BrainInputs, ecs_entity_t)
zox_memory_component(BrainOutputs, ecs_entity_t)
zox_memory_component(BrainLinks, ecs_entity_t)
#include "data/settings.c"
#include "prefabs/prefabs.c"
#include "util/neuron_util.c"
#include "util/build_test_brain.c"
#include "systems/_.c"
#include "debug/_.c"

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
    define_systems_neurals(world);
    spawn_prefabs_neurals(world);
    // spawn_test_brain(world);
zox_end_module(Neurals)

#endif

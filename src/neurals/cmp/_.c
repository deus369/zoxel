zox_tag(Brain);
zox_tag(Neuron);
zox_tag(Connection);
zox_tag(InputNeuron);
zox_tag(OutputNeuron);
zoxc_float(Weight);                     //! The weight of the neural connection
zoxc_float(Signal);                     //! If the signal is sending
zoxc_float(Transfer);                   //! The signal value of a connection
zoxc(ConnectionData, entity2);     //! The weight of the neural connection
zoxc_byte(BrainDirty);
zoxc_entity(BrainLink);
zoxc_arrayd(BrainInputs, ecs_entity_t)
zoxc_arrayd(BrainOutputs, ecs_entity_t)
zoxc_arrayd(BrainLinks, ecs_entity_t)

void define_components_neurals(ecs* world) {
    zox_define_tag(Brain);
    zox_define_tag(Neuron);
    zox_define_tag(Connection);
    zox_define_tag(InputNeuron);
    zox_define_tag(OutputNeuron);
    zox_define_component_float(Weight);
    zox_define_component_float(Signal);
    zox_define_component_float(Transfer);
    zox_define_component(ConnectionData);
    zox_define_component_byte(BrainDirty);
    zox_define_component_entity(BrainLink);
    zox_define_memory_component(BrainInputs);
    zox_define_memory_component(BrainOutputs);
    zox_define_memory_component(BrainLinks);
}
#include "input_neuron_system.c"
#include "feed_forward_system.c"
#include "neuron_feed_forward_system.c"
#include "connection_render_system.c"
#include "neuron_render_system.c"

void define_systems_neurals(ecs_world_t* world) {
    // zox_system(NeuronInputSystem, EcsOnUpdate, [none] InputNeuron) //  [out] Transfer,
    zox_system(LinkFeedForwardSystem, EcsPostUpdate,
        [in] ConnectionData,
        [out] Weight,
        [out] Signal,
        [out] Transfer,
        [none] Connection)
    zox_system(NeuronFeedForwardSystem, EcsOnUpdate,
        [out] Signal,
        [none] Neuron,
        [none] !OutputNeuron)

#ifdef zox_render_brain
    zox_system_1(NeuronRenderSystem, zox_pip_mainthread,
        [in] transforms2.Position2D,
        [none] Neuron)
    zox_system_1(ConnectionRenderSystem, zox_pip_mainthread,
        [in] ConnectionData,
        [in] Weight,
        [in] Signal,
        [in] Transfer,
        [none] Connection)
#endif
}
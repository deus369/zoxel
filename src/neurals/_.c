#if !defined(zoxm_neurals) && defined(zoxm_nodes)
#define zoxm_neurals

#include "data/settings.c"
#include "cmp/_.c"
#include "prefabs/prefabs.c"
#include "util/neuron_util.c"
#include "util/build_test_brain.c"
#include "systems/_.c"
#include "debug/_.c"

zox_begin_module(Neurals)
    define_components_neurals(world);
    define_systems_neurals(world);
    add_hook_spawn_prefabs(spawn_prefabs_neurals);
    // spawn_test_brain(world);
zox_end_module(Neurals)

#endif

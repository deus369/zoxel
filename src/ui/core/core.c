#ifndef zox_mod_ui_core
#define zox_mod_ui_core

#include "data/data.c"
#include "util/util.c"
#include "prefabs/prefabs.c"
#include "systems/systems.c"

zox_begin_module(ElementsCore)
    define_components_elements_core(world);
    define_systems_elements_core(world);
    spawn_prefabs_ui_core(world);
zox_end_module(ElementsCore)

#endif

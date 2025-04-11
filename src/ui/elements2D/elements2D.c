#ifndef zox_elements2D
#define zox_elements2D

#include "data/data.c"
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "systems/systems.c"

zox_begin_module(Elements2D)
    define_components_elements2D(world);
    define_systems_elements2D(world);
    spawn_prefabs_elements(world);
    // zox_log("FRAME? %s\n", zox_get_namespace(Frame))
    // add_hook_key_down(test_key_element_front2D);
zox_end_module(Elements2D)

#endif
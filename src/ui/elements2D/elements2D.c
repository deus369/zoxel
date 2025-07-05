#ifndef zox_elements2D
#define zox_elements2D

#include "settings/_.c"
#include "data/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Elements2D)
    define_components_elements2D(world);
    define_systems_elements2D(world);
    spawn_prefabs_elements(world);
    // add_hook_key_down(test_key_element_front2D);
zox_end_module(Elements2D)

#endif
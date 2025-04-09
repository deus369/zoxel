#ifndef zox_elements2D
#define zox_elements2D

#include "data/data.c"
#include "data/components.c"
#include "prefabs/prefabs.c"
#include "util/button_event_close_window.c"
#include "util/resize_util.c"
#include "util/navigation_util.c"
#include "util/position_util.c"
#include "util/debug.c"
#include "systems/systems.c"

zox_begin_module(Elements2D)
    define_components_elements2D(world);
    define_systems_elements2D(world);
    spawn_prefabs_elements(world);
    // add_hook_key_down(test_key_element_front2D);
zox_end_module(Elements2D)

#endif

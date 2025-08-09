#ifndef zoxm_ui_core
#define zoxm_ui_core

// todo: move PixelPosition etc to Transforms/Grid2D - idk what to call it
#include "settings/_.c"
#include "components/_.c"
#include "data/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "spawn/_.c"
#include "systems/_.c"

zox_begin_module(ElementsCore)
    define_components_elements_core(world);
    define_systems_elements_core(world);
    add_hook_spawn_prefabs(spawn_prefabs_ui_core);
zox_end_module(ElementsCore)

#endif
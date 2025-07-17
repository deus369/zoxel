#ifndef zox_elements2D
#define zox_elements2D

#include "settings/_.c"
#include "components/_.c"
#include "data/_.c"
#include "prefabs/_.c"
#include "spawn/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Elements2)
    define_components_elements2D(world);
    define_systems_elements2D(world);
    spawn_prefabs_elements(world);
zox_end_module(Elements2)

#endif
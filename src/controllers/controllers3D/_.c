#ifndef zox_mod_controllers3D
#define zox_mod_controllers3D

#include "settings/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Controllers3D)
    define_components_controllers3D(world);
    define_systems_controllers3D(world);
    spawn_prefabs_players3D(world);
zox_end_module(Controllers3D)

#endif
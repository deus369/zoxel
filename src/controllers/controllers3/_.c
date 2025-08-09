#ifndef zoxm_controllers3D
#define zoxm_controllers3D

#include "settings/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "spawn/_.c"
#include "systems/_.c"
#include "debug/_.c"

zox_begin_module(Controllers3)
    define_components_controllers3D(world);
    define_systems_controllers3D(world);
    add_hook_spawn_prefabs(spawn_prefabs_players3D);
zox_end_module(Controllers3)

#endif
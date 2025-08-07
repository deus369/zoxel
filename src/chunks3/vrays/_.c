// VoxelRays into your heart <3
#ifndef zoxm_vrays
#define zoxm_vrays

#include "components/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Vrays)
    define_components_vrays(world);
    define_systems_vrays(world);
zox_end_module(Vrays)

#endif
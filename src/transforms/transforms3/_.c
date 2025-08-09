#ifndef zoxm_transforms3
#define zoxm_transforms3

#define zox_transforms_stage EcsPreStore // EcsPostUpdate | EcsPreStore
#include "cmp/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Transforms3)
    define_components_transforms3(world);
    zox_define_systems_transforms3D(world);
zox_end_module(Transforms3)

#endif
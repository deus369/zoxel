#ifndef zoxm_collisions3
#define zoxm_collisions3

// todo: add AABB (then detailed voxel) to Sphere [overlap] events for pickups
// remember: no line detection for boxes, if velocity exceeds clipping it will fall through map!
#include "data/settings.c"
#include "data/axis.c"
#include "components/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Collisions3)
    define_components_collisions3(world);
    define_systems_collisions3(world);
zox_end_module(Collisions3)

#endif
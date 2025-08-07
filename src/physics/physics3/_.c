#if !defined(zoxm_physics3) && defined(zoxm_transforms3)
#define zoxm_physics3

#include "settings/_.c"
#include "components/_.c"
#include "util/_.c"
#include "systems/_.c"
#include "collisions3D/_.c"

zox_begin_module(Physics3)
    zox_define_components_physics3(world);
    define_systems_physics3(world);
    zox_import_module(Collisions3)
zox_end_module(Physics3)

#endif
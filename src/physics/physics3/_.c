#if !defined(zox_mod_physics3) && defined(zox_mod_transforms3)
#define zox_mod_physics3

#include "settings/_.c"
#include "components/_.c"
#include "util/_.c"
#include "systems/_.c"
#include "collisions3D/_.c"

zox_begin_module(Physics3)
    zox_define_components_physics3(world);
    define_systems_physics3(world);
    zox_import_module(Collisions3D)
zox_end_module(Physics3)

#endif
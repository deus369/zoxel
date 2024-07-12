#if !defined(zox_mod_pickups) && defined(zox_mod_cubes)
#define zox_mod_pickups

zox_declare_tag(Pickup)
#include "prefabs/prefabs.c"
// #include "systems/pickup_debug_system.c"

zox_begin_module(Pickups)
zox_define_tag(Pickup)
spawn_prefabs_pickups(world);
zoxel_end_module(Pickups)

#endif

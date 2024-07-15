#if !defined(zox_mod_pickups) && defined(zox_mod_cubes)
#define zox_mod_pickups

// #define zox_prefabs_non_textured
#define pickup_rotaion_speed 40
zox_declare_tag(Pickup)
zox_declare_tag(PickUpperer)
zox_component_byte(PickedUp)
#include "data/pickup_states.c"
#include "util/collision_util.c"
#include "prefabs/prefabs.c"
#include "systems/pickup_sound_system.c"
zox_increment_system(PickedUp, pickup_state_end)

zox_begin_module(Pickups)
zox_define_tag(Pickup)
zox_define_tag(PickUpperer)
zox_define_component_byte(PickedUp)
zox_define_increment_system(PickedUp, EcsOnLoad, [none] Pickup)
zox_system_1(PickupSoundSystem, zox_pip_mainthread, [in] PickedUp, [none] Pickup)
spawn_prefabs_pickups(world);
zoxel_end_module(Pickups)

#endif

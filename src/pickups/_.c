#if !defined(zoxm_pickups) && defined(zoxm_cubes)
#define zoxm_pickups

// #define zox_prefabs_non_textured
#define pickup_rotaion_speed 40
zox_tag(Pickup);
zox_tag(PickUpperer);
zoxc_byte(PickedUp);
#include "data/pickup_states.c"
#include "util/collision_util.c"
#include "prefabs/prefabs.c"
#include "systems/pickup_sound_system.c"
zox_increment_system(PickedUp, pickup_state_end);

zox_begin_module(Pickups)
    zox_define_tag(Pickup);
    zox_define_tag(PickUpperer);
    zox_define_component_byte(PickedUp);
    zoxd_system_increment(PickedUp, [none] Pickup);
    zox_system_1(PickupSoundSystem, zoxp_mainthread,
        [in] PickedUp,
        [none] Pickup)
    add_hook_spawn_prefabs(spawn_prefabs_pickups);
zox_end_module(Pickups)

#endif
#if !defined(zox_mod_ai) && defined(zox_mod_characters)
#define zox_mod_ai

#include "data/behaviours.c"
zox_component_byte(Behaviour)
zox_declare_tag(Wanderer)
#include "prefabs/prefabs.c"
#include "systems/wander_system.c"

zox_begin_module(AI)
    zox_define_component_byte(Behaviour)
    zox_define_tag(Wanderer)
    zox_system(WanderSystem, EcsOnUpdate, [none] Wanderer, [in] Rotation3D,  [in] Velocity3D, [out] Acceleration3D, [in] Omega3D, [out] Alpha3D, [in] DisableMovement)
    spawn_prefabs_ai(world);
zox_end_module(AI)

#endif

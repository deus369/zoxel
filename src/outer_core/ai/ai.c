#ifndef zoxel_ai
#define zoxel_ai

// used for the npcs to make decisions and plan actions
zox_declare_tag(Wanderer)
#include "systems/wander_system.c"

zox_begin_module(AI)
// components & systems
zox_define_tag(Wanderer)
zox_system(WanderSystem, EcsOnUpdate, [none] Wanderer, [in] Rotation3D,  [in] Velocity3D, [out] Acceleration3D,  [in] Omega3D, [out] Alpha3D)
zoxel_end_module(AI)

#endif

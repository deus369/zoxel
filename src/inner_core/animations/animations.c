#ifndef zoxel_animations
#define zoxel_animations

zox_component(EternalRotation, float4)
#include "systems/eternal_rotation_system.c"    // move this to animation module

zox_begin_module(Animations)
zox_define_component(EternalRotation)
zox_system(EternalRotationSystem, EcsOnUpdate, [out] Rotation3D, [in] EternalRotation)
zoxel_end_module(Animations)

#endif
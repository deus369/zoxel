#ifndef zoxel_animations
#define zoxel_animations

zoxel_component(EternalRotation, float4)
#include "systems/eternal_rotation_system.c"    // move this to animation module

zoxel_begin_module(Animations)
zoxel_define_component(EternalRotation)
zoxel_system(world, EternalRotationSystem, EcsOnUpdate, [out] Rotation3D, [in] EternalRotation);  // _main_thread
zoxel_end_module(Animations)

#endif
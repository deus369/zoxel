#ifndef zoxel_animations
#define zoxel_animations

#define zox_animation_none 0
#define zox_animation_idle 1
#define zox_animation_moving 2
#define zox_animation_shrink 3
#define zox_animation_fadeout 4
#define zox_animation_fadein 5
// components
zox_byte_component(AnimationState)
zox_time_component(AnimationStart)
zox_component(EternalRotation, float4)
// systems
#include "systems/eternal_rotation_system.c"    // move this to animation module
#include "systems/shrink_system.c"
#include "systems/idle_system.c"
#include "systems/fadeout_system.c"

zox_begin_module(Animations)
// components
zox_define_component(AnimationState)
zox_define_component(AnimationStart)
zox_define_component(EternalRotation)
// systems
zox_system(EternalRotationSystem, EcsOnUpdate, [out] Rotation3D, [in] EternalRotation)
zox_system(ShrinkSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
zox_system(IdleSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
zox_system(FadeoutSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Alpha)
zox_system(FadeinSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Alpha)
zoxel_end_module(Animations)

#endif
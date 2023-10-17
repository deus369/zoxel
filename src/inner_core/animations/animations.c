#ifndef zoxel_animations
#define zoxel_animations

// Animation Structure
//  > characters can have many animations
//  > animation instance data contains the time value of the animation starting
//  > animation data contains the lerp start and end values
//  > an animation contains many curves
//      > a curve has a property, requires a system to lerp that property (can macro this system)
//  > our death animation consists of a bunch of curves, each curve will lerp different properties
//      > scale, color, etc
// todo:
//  > animation curve editor simplified, just show animation and list of curve/properties it has

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
zox_memory_component(AnimationLinks, ecs_entity_t)
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
zox_define_memory_component(AnimationLinks)
// systems
zox_system(EternalRotationSystem, EcsOnUpdate, [out] Rotation3D, [in] EternalRotation)
zox_system(ShrinkSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
zox_system(IdleSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
zox_system(FadeoutSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Alpha)
zox_system(FadeinSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Alpha)
zoxel_end_module(Animations)

#endif

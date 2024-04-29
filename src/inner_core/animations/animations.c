#ifndef zoxel_animations
#define zoxel_animations

// currently we are animating components by hand
// later we must customly choose what curves to apply to what components
#include "data/animation_states.c"
// components
zox_component_byte(AnimationState)
zox_component_double(AnimationStart) // double is time?
zox_component_double(AnimationLength)
zox_component_double(AnimationDelay)
zox_component_float4(EternalRotation)
zox_memory_component(AnimationSequence, unsigned char) // a sequence of animation states
zox_memory_component(AnimationTimes, double) // a sequence of animation times
zox_memory_component(AnimationLinks, ecs_entity_t)
// systems
#include "systems/eternal_rotation_system.c"    // move this to animation module
#include "systems/shrink_system.c"
#include "systems/idle_system.c"
#include "systems/fadeout_system.c"
#include "systems/fadein_system.c"
#include "systems/animation_sequence_system.c"

zox_begin_module(Animations)
// components
zox_define_component_byte(AnimationState)
zox_define_component_double(AnimationStart)
zox_define_component_double(AnimationLength)
zox_define_component_double(AnimationDelay)
zox_define_component_float4(EternalRotation)
zox_define_memory_component(AnimationLinks)
zox_define_memory_component(AnimationSequence)
zox_define_memory_component(AnimationTimes)
// systems
zox_system(EternalRotationSystem, EcsOnUpdate, [out] Rotation3D, [in] EternalRotation)
zox_system(ShrinkSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
zox_system(IdleSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
zox_system(FadeoutSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [in] AnimationLength, [in] AnimationDelay, [out] Alpha)
zox_system(FadeinSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [in] AnimationLength, [in] AnimationDelay, [out] Alpha)
zox_system(AnimationSequenceSystem, EcsOnUpdate, [in] AnimationSequence, [in] AnimationLength, [in] AnimationDelay, [out] AnimationStart, [out] AnimationState)
zoxel_end_module(Animations)

#endif

#ifndef zoxm_animations
#define zoxm_animations

// todo: lerp position from A to B entities
// currently we are animating components by hand
// later we must customly choose what curves to apply to what components
#include "data/animation_states.c"
zox_tag(OscillatePosition3D);
zoxc_float3(OscillateStartPosition3D);
zoxc_float3(OscillateDeltaPosition3D);
zoxc_byte(AnimationState);
zoxc_double(AnimationStart);
zoxc_double(AnimationLength);
zoxc_double(AnimationDelay);
zoxc_float4(EternalRotation);
zoxc_arrayd(AnimationLinks, ecs_entity_t)
zoxc_float(AnimateSourceFloat);
zoxc_float(AnimateTargetFloat);
zoxc_float(FadeOutEvent);
// sequencing
zoxc_byte(AnimationIndex);
zoxc_arrayd(AnimationSequence, byte) // a sequence of animation states
zoxc_arrayd(AnimationTimes, double) // a sequence of animation times
zoxc_arrayd(AnimationTargets, float) // a sequence of animation target values
#include "systems/eternal_rotation_system.c"    // move this to animation module
#include "systems/shrink_system.c"
#include "systems/idle_system.c"
#include "systems/fadeout_system.c"
#include "systems/fadein_system.c"
#include "systems/animation_sequence_system.c"
#include "systems/animate_alpha_system.c"
#include "systems/oscillate_system.c"

zox_begin_module(Animations)
    zox_define_tag(OscillatePosition3D);
    zox_define_component_float3(OscillateStartPosition3D);
    zox_define_component_float3(OscillateDeltaPosition3D);
    // old
    zoxd_byte(AnimationState);
    zox_define_component_double(AnimationDelay);
    zox_define_component_float4(EternalRotation);
    // single anim
    zox_define_component_double(AnimationStart);
    zox_define_component_double(AnimationLength);
    zox_define_component_float(AnimateSourceFloat);
    zox_define_component_float(AnimateTargetFloat);
    // sequencing
    zoxd_byte(AnimationIndex);
    zox_define_memory_component(AnimationSequence);
    zox_define_memory_component(AnimationTimes);
    zox_define_memory_component(AnimationTargets);
    // defined events
    zox_define_component_float(FadeOutEvent);
    // seperating animations
    zox_define_memory_component(AnimationLinks);
    zox_system(EternalRotationSystem, EcsOnUpdate,
        [in] EternalRotation,
        [out] transforms3.Rotation3D)
    zox_system(ShrinkSystem, EcsOnUpdate,
        [in] AnimationState,
        [in] AnimationStart,
        [out] transforms.Scale1D)
    zox_system(IdleSystem, EcsOnUpdate,
        [in] AnimationState,
        [in] AnimationStart,
        [out] transforms.Scale1D)
    /*zox_system(FadeinSystem, EcsOnUpdate,
        [in] AnimationState,
        [in] AnimationStart,
        [in] AnimationLength,
        [in] AnimationDelay,
        [out] rendering.Alpha)*/
    zox_system(AnimationSequenceSystem, EcsPostUpdate,
        [in] AnimationSequence,
        [in] AnimationTimes,
        [in] AnimationTargets,
        [in] AnimationDelay,
        [out] AnimationIndex,
        [out] AnimationLength,
        [out] AnimationStart,
        [out] AnimationState)
    zox_system(AnimateAlphaSystem, EcsOnUpdate,
        [in] AnimationState,
        [in] AnimationStart,
        [in] AnimationLength,
        [in] AnimationDelay,
        [in] AnimateSourceFloat,
        [in] AnimateTargetFloat,
        [out] rendering.Alpha)
    zox_system(FadeoutSystem, EcsOnUpdate,
        [in] FadeOutEvent,
        [in] AnimationStart,
        [out] rendering.Alpha)
    zox_system(OscillateSystem, EcsOnUpdate,
        [in] OscillateStartPosition3D,
        [in] OscillateDeltaPosition3D,
        [out] transforms3.LocalPosition3D,
        [none] OscillatePosition3D)
zox_end_module(Animations)

#endif

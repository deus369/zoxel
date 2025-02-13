#ifndef zox_mod_animations
#define zox_mod_animations

// todo: lerp position from A to B entities
// currently we are animating components by hand
// later we must customly choose what curves to apply to what components
#include "data/animation_states.c"
zox_declare_tag(OscillatePosition3D)
zox_component_float3(OscillateStartPosition3D)
zox_component_byte(AnimationState)
zox_component_double(AnimationStart) // double is time?
zox_component_double(AnimationLength)
zox_component_double(AnimationDelay)
zox_component_float4(EternalRotation)
zox_memory_component(AnimationLinks, ecs_entity_t)
zox_component_float(AnimateSourceFloat)
zox_component_float(AnimateTargetFloat)
zox_component_float(FadeOutEvent)
// sequencing
zox_component_byte(AnimationIndex)
zox_memory_component(AnimationSequence, unsigned char) // a sequence of animation states
zox_memory_component(AnimationTimes, double) // a sequence of animation times
zox_memory_component(AnimationTargets, float) // a sequence of animation target values
#include "systems/eternal_rotation_system.c"    // move this to animation module
#include "systems/shrink_system.c"
#include "systems/idle_system.c"
#include "systems/fadeout_system.c"
#include "systems/fadein_system.c"
#include "systems/animation_sequence_system.c"
#include "systems/animate_alpha_system.c"
#include "systems/oscillate_system.c"

void prefab_add_animation(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, AnimationIndex, { 0 })
    zox_prefab_add(e, AnimationSequence)
    zox_prefab_add(e, AnimationTimes)
    zox_prefab_add(e, AnimationTargets)
}

zox_begin_module(Animations)
    zox_define_tag(OscillatePosition3D)
    zox_define_component_float3(OscillateStartPosition3D)
    // old
    zox_define_component_byte(AnimationState)
    zox_define_component_double(AnimationDelay)
    zox_define_component_float4(EternalRotation)
    // single anim
    zox_define_component_double(AnimationStart)
    zox_define_component_double(AnimationLength)
    zox_define_component_float(AnimateSourceFloat)
    zox_define_component_float(AnimateTargetFloat)
    // sequencing
    zox_define_component_byte(AnimationIndex)
    zox_define_memory_component(AnimationSequence)
    zox_define_memory_component(AnimationTimes)
    zox_define_memory_component(AnimationTargets)
    // defined events
    zox_define_component_float(FadeOutEvent)
    // seperating animations
    zox_define_memory_component(AnimationLinks)
    zox_system(EternalRotationSystem, EcsOnUpdate, [in] EternalRotation, [out] Rotation3D)
    zox_system(ShrinkSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
    zox_system(IdleSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [out] Scale1D)
    zox_system(FadeinSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [in] AnimationLength, [in] AnimationDelay, [out] Alpha)
    zox_system(AnimationSequenceSystem, EcsPostUpdate, [in] AnimationSequence, [in] AnimationTimes, [in] AnimationTargets, [in] AnimationDelay,  [out] AnimationIndex, [out] AnimationLength, [out] AnimationStart, [out] AnimationState)
    zox_system(AnimateAlphaSystem, EcsOnUpdate, [in] AnimationState, [in] AnimationStart, [in] AnimationLength, [in] AnimationDelay, [in] AnimateSourceFloat, [in] AnimateTargetFloat, [out] Alpha)
    zox_system(FadeoutSystem, EcsOnUpdate, [in] FadeOutEvent, [in] AnimationStart, [out] Alpha)
    zox_system(OscillateSystem, EcsOnUpdate, [in] OscillateStartPosition3D, [out] LocalPosition3D, [none] OscillatePosition3D)
zox_end_module(Animations)

#endif

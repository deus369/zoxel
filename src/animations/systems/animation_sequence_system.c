void AnimationSequenceSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(AnimationSequence)
    zox_sys_in(AnimationTimes)
    zox_sys_in(AnimationTargets)
    zox_sys_in(AnimationDelay)
    zox_sys_out(AnimationIndex)
    zox_sys_out(AnimationLength)
    zox_sys_out(AnimationStart)
    zox_sys_out(AnimationState)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(AnimationTimes, animationTimes)
        zox_sys_i(AnimationTargets, animationTargets)
        zox_sys_i(AnimationDelay, animationDelay)
        zox_sys_i(AnimationSequence, animationSequence)
        zox_sys_o(AnimationStart, animationStart)
        zox_sys_o(AnimationLength, animationLength)
        zox_sys_o(AnimationState, animationState)
        zox_sys_o(AnimationIndex, animationIndex)
        if (animationIndex->value == 255) {
            continue;
        }
        if (!animationSequence->length) {
            continue;
        }
        if (animationIndex->value > animationSequence->length) {
            animationIndex->value = 255;
            continue;
        }
        byte is_anim_over = 0;
        if (animationIndex->value == 0) {
            is_anim_over = 1;
        } else {
            const double animation_time = (time - (animationStart->value + animationDelay->value)) / animationLength->value;
            is_anim_over = animation_time >= 1;
        }
        if (is_anim_over) {
            if (animationIndex->value == animationSequence->length) {
                animationIndex->value = 255;
                animationState->value = zox_animation_none;
            } else {
                animationStart->value = time;
                animationState->value = animationSequence->value[animationIndex->value];
                animationLength->value = animationTimes->value[animationIndex->value];
                zox_sys_e()
                // if alpha
                float source_float = zox_gett_value(e, Alpha);
                float target_float = animationTargets->value[animationIndex->value];
                zox_set(e, AnimateSourceFloat, { source_float })
                zox_set(e, AnimateTargetFloat, { target_float })
                // increase index
                animationIndex->value = animationIndex->value + 1;
            }
        }
    }
} zoxd_system(AnimationSequenceSystem)
void AnimationSequenceSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_field_world()
    zox_field_in(AnimationSequence, animationSequences, 1)
    zox_field_in(AnimationTimes, animationTimess, 2)
    zox_field_in(AnimationTargets, animationTargetss, 3)
    zox_field_in(AnimationDelay, animationDelays, 4)
    zox_field_out(AnimationIndex, animationIndexs, 5)
    zox_field_out(AnimationLength, animationLengths, 6)
    zox_field_out(AnimationStart, animationStarts, 7)
    zox_field_out(AnimationState, animationStates, 8)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(AnimationIndex, animationIndexs, animationIndex)
        if (animationIndex->value == 255) {
            continue;
        }
        zox_field_i(AnimationSequence, animationSequences, animationSequence)
        if (!animationSequence->length) {
            continue;
        }
        if (animationIndex->value > animationSequence->length) {
            animationIndex->value = 255;
            continue;
        }
        zox_field_i(AnimationTimes, animationTimess, animationTimes)
        zox_field_i(AnimationTargets, animationTargetss, animationTargets)
        zox_field_i(AnimationDelay, animationDelays, animationDelay)
        zox_field_o(AnimationStart, animationStarts, animationStart)
        zox_field_o(AnimationLength, animationLengths, animationLength)
        zox_field_o(AnimationState, animationStates, animationState)
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
                zox_field_e()
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
} zox_declare_system(AnimationSequenceSystem)
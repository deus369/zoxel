void AnimationSequenceSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_field_in(AnimationSequence, animationSequences, 1)
    zox_field_in(AnimationLength, animationLengths, 2)
    zox_field_in(AnimationDelay, animationDelays, 3)
    zox_field_out(AnimationStart, animationStarts, 4)
    zox_field_out(AnimationState, animationStates, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(AnimationState, animationStates, animationState)
        if (animationState->value == zox_animation_none) continue;
        zox_field_i_in(AnimationSequence, animationSequences, animationSequence)
        if (animationSequence->length == 0) continue;
        zox_field_i_in(AnimationLength, animationLengths, animationLength)
        zox_field_i_in(AnimationDelay, animationDelays, animationDelay)
        zox_field_i_out(AnimationStart, animationStarts, animationStart)
        const double animation_time = (time - (animationStart->value + animationDelay->value)) / animationLength->value;
        if (animation_time >= 1) {
            for (int j = 0; j < animationSequence->length; j++) {
                if (animationSequence->value[j] == animationState->value) {
                    if (j == animationSequence->length - 1) animationState->value = zox_animation_none;
                    else {
                        animationState->value = animationSequence->value[j + 1];
                        animationStart->value = time;
                    }
                    break;
                }
            }
        }
    }
} zox_declare_system(AnimationSequenceSystem)

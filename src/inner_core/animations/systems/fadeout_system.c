// a simple alpha animation
void FadeoutSystem(ecs_iter_t *it) {
    /*const double time = zox_current_time;
    zox_field_in(AnimationState, animationTypes, 1)
    zox_field_in(AnimationStart, animationStarts, 2)
    zox_field_in(AnimationLength, animationLengths, 3)
    zox_field_in(AnimationDelay, animationDelays, 4)
    zox_field_out(Alpha, alphas, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(AnimationState, animationTypes, animationType)
        if (animationType->value != zox_animation_fadeout) continue;
        zox_field_i_in(AnimationStart, animationStarts, animationStart)
        zox_field_i_in(AnimationLength, animationLengths, animationLength)
        zox_field_i_in(AnimationDelay, animationDelays, animationDelay)
        zox_field_i_out(Alpha, alphas, alpha)
        double animation_time = (time - (animationStart->value + animationDelay->value)) / animationLength->value;
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        alpha->value = float_lerp(1, 0, animation_time);
    }*/
} zox_declare_system(FadeoutSystem)

// this animates alpha over time usingg  lerp
// todo: make this a macro to animate a component - make RenderDisabled an event?
void AnimateAlphaSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_field_in(AnimationState, animationTypes, 1)
    zox_field_in(AnimationStart, animationStarts, 2)
    zox_field_in(AnimationLength, animationLengths, 3)
    zox_field_in(AnimationDelay, animationDelays, 4)
    zox_field_in(AnimateSourceFloat, animateSourceFloats, 5)
    zox_field_in(AnimateTargetFloat, animateTargetFloats, 6)
    zox_field_out(Alpha, alphas, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(AnimationState, animationTypes, animationType)
        if (animationType->value != zox_animate_alpha) continue;
        zox_field_i(AnimationStart, animationStarts, animationStart)
        zox_field_i(AnimationLength, animationLengths, animationLength)
        zox_field_i(AnimationDelay, animationDelays, animationDelay)
        zox_field_i(AnimateSourceFloat, animateSourceFloats, animateSourceFloat)
        zox_field_i(AnimateTargetFloat, animateTargetFloats, animateTargetFloat)
        zox_field_o(Alpha, alphas, alpha)
        double animation_time = (time - (animationStart->value + animationDelay->value)) / animationLength->value;
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        alpha->value = float_lerp(animateSourceFloat->value, animateTargetFloat->value, animation_time);
        // zox_log("   > animating alpha [%f] at time [%f] source [%f] target [%f]\n", alpha->value, animation_time, animateSourceFloat->value, animateTargetFloat->value)
        // if (animation_time == 1 && alpha->value == 0) zox_set(it->entities[i], RenderDisabled, { 1 })
    }
} zox_declare_system(AnimateAlphaSystem)

// need to add event at end that disables rendering

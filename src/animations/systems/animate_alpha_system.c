// this animates alpha over time usingg  lerp
// todo: make this a macro to animate a component - make RenderDisabled an event?
void AnimateAlphaSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_sys_begin()
    zox_sys_in(AnimationState)
    zox_sys_in(AnimationStart)
    zox_sys_in(AnimationLength)
    zox_sys_in(AnimationDelay)
    zox_sys_in(AnimateSourceFloat)
    zox_sys_in(AnimateTargetFloat)
    zox_sys_out(Alpha)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(AnimationState, animationType)
        zox_sys_i(AnimationStart, animationStart)
        zox_sys_i(AnimationLength, animationLength)
        zox_sys_i(AnimationDelay, animationDelay)
        zox_sys_i(AnimateSourceFloat, animateSourceFloat)
        zox_sys_i(AnimateTargetFloat, animateTargetFloat)
        zox_sys_o(Alpha, alpha)
        if (animationType->value != zox_animate_alpha) {
            continue;
        }
        double animation_time = (time - (animationStart->value + animationDelay->value)) / animationLength->value;
        if (animation_time < 0) {
            animation_time = 0;
        } else if (animation_time > 1) {
            animation_time = 1;
        }
        alpha->value = float_lerp(animateSourceFloat->value, animateTargetFloat->value, animation_time);
    }
} zox_declare_system(AnimateAlphaSystem)
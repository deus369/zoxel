// a simple shrink system
void ShrinkSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_sys_begin()
    zox_sys_in(AnimationState)
    zox_sys_in(AnimationStart)
    zox_sys_out(Scale1D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(AnimationState, animationType)
        zox_sys_i(AnimationStart, animationStart)
        zox_sys_o(Scale1D, scale1D)
        if (animationType->value != zox_animation_shrink) {
            continue;
        }
        double animation_time = time - animationStart->value;
        // limit animation_time
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        scale1D->value = float_lerp(1, 0, animation_time);
    }
} zoxd_system(ShrinkSystem)

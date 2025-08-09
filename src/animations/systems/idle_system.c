// a simple idle scale animation
void IdleSystem(ecs_iter_t *it) {
    const float idle_default_scale = 1.0f;
    const float idle_scale_addition = 0.02f;
    const float idle_animation_speed = 4.0f;
    const double time = zox_current_time;
    zox_sys_begin()
    zox_sys_in(AnimationState)
    zox_sys_in(AnimationStart)
    zox_sys_out(Scale1D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(AnimationState, animationType)
        zox_sys_i(AnimationStart, animationStart)
        zox_sys_o(Scale1D, scale1D)
        if (animationType->value != zox_animation_idle) {
            continue;
        }
        const double animation_time = time - animationStart->value;
        scale1D->value = idle_default_scale + idle_scale_addition * sin(animation_time * idle_animation_speed);
    }
} zoxd_system(IdleSystem)

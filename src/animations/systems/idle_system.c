// a simple idle scale animation
void IdleSystem(ecs_iter_t *it) {
    const float idle_default_scale = 1.0f;
    const float idle_scale_addition = 0.02f;
    const float idle_animation_speed = 4.0f;
    const double time = zox_current_time;
    zox_field_in(AnimationState, animationTypes, 1)
    zox_field_in(AnimationStart, animationStarts, 2)
    zox_field_out(Scale1D, scale1Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(AnimationState, animationTypes, animationType)
        if (animationType->value != zox_animation_idle) continue;
        zox_field_i(AnimationStart, animationStarts, animationStart)
        zox_field_o(Scale1D, scale1Ds, scale1D)
        const double animation_time = time - animationStart->value;
        scale1D->value = idle_default_scale + idle_scale_addition * sin(animation_time * idle_animation_speed);
    }
} zox_declare_system(IdleSystem)

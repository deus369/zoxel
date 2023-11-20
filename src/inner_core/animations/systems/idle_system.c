// a simple idle scale animation
void IdleSystem(ecs_iter_t *it) {
    const float idle_default_scale = 1.0f;
    const float idle_scale_addition = 0.02f;
    const float idle_animation_speed = 4.0f;
    double time = zox_current_time;
    const AnimationState *animationTypes = ecs_field(it, AnimationState, 1);
    const AnimationStart *animationStarts = ecs_field(it, AnimationStart, 2);
    Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    for (int i = 0; i < it->count; i++) {
        const AnimationState *animationType = &animationTypes[i];
        if (animationType->value != zox_animation_idle) continue;
        const AnimationStart *animationStart = &animationStarts[i];
        double animation_time = time - animationStart->value;
        Scale1D *scale1D = &scale1Ds[i];
        scale1D->value = idle_default_scale + idle_scale_addition * sin(animation_time * idle_animation_speed);
    }
} zox_declare_system(IdleSystem)

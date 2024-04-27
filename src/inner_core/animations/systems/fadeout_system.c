// a simple alpha animation

void FadeoutSystem(ecs_iter_t *it) {
    float delay = 1.0f;
    float animation_length = 2.0f;
    double time = zox_current_time;
    const AnimationState *animationTypes = ecs_field(it, AnimationState, 1);
    const AnimationStart *animationStarts = ecs_field(it, AnimationStart, 2);
    Alpha *alphas = ecs_field(it, Alpha, 3);
    for (int i = 0; i < it->count; i++) {
        const AnimationState *animationType = &animationTypes[i];
        if (animationType->value != zox_animation_fadeout) continue;
        const AnimationStart *animationStart = &animationStarts[i];
        double animation_time = time - (animationStart->value + delay);
        animation_time /= animation_length;
        // limit animation_time
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        Alpha *alpha = &alphas[i];
        alpha->value = float_lerp(1, 0, animation_time);
    }
} zox_declare_system(FadeoutSystem)

// a copy of fadeout
void FadeinSystem(ecs_iter_t *it) {
    float speed = 0.2f;
    double time = zox_current_time;
    const AnimationState *animationTypes = ecs_field(it, AnimationState, 1);
    const AnimationStart *animationStarts = ecs_field(it, AnimationStart, 2);
    Alpha *alphas = ecs_field(it, Alpha, 3);
    for (int i = 0; i < it->count; i++) {
        const AnimationState *animationType = &animationTypes[i];
        if (animationType->value != zox_animation_fadein) continue;
        const AnimationStart *animationStart = &animationStarts[i];
        double animation_time = time - animationStart->value;
        animation_time *= speed;
        // limit animation_time
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        Alpha *alpha = &alphas[i];
        alpha->value = float_lerp(1, 0, animation_time);
    }
} zox_declare_system(FadeinSystem)

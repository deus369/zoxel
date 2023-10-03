// a simple shrink system
void ShrinkSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    double time = zox_current_time;
    const AnimationState *animationTypes = ecs_field(it, AnimationState, 1);
    const AnimationStart *animationStarts = ecs_field(it, AnimationStart, 2);
    Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    for (int i = 0; i < it->count; i++) {
        const AnimationState *animationType = &animationTypes[i];
        if (animationType->value != zox_animation_shrink) continue;
        const AnimationStart *animationStart = &animationStarts[i];
        double animation_time = time - animationStart->value;
        // limit animation_time
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        Scale1D *scale1D = &scale1Ds[i];
        scale1D->value = float_lerp(1, 0, animation_time);
    }
} zox_declare_system(ShrinkSystem)
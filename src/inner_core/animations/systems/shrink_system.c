// a simple shrink system
void ShrinkSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_field_in(AnimationState, animationTypes, 1)
    zox_field_in(AnimationStart, animationStarts, 2)
    zox_field_out(Scale1D, scale1Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(AnimationState, animationTypes, animationType)
        if (animationType->value != zox_animation_shrink) continue;
        zox_field_i_in(AnimationStart, animationStarts, animationStart)
        zox_field_i_out(Scale1D, scale1Ds, scale1D)
        double animation_time = time - animationStart->value;
        // limit animation_time
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        scale1D->value = float_lerp(1, 0, animation_time);
    }
} zox_declare_system(ShrinkSystem)

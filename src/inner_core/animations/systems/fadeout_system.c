// a simple alpha animation
void zox_prefab_add_animation_event(ecs_world_t *world, const ecs_entity_t e, float length) {
    zox_prefab_set(e, FadeOutEvent, { length })
    zox_prefab_set(e, Alpha, { 1 })
    zox_prefab_set(e, AnimationStart, { 0 })
}

void FadeoutSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_field_in(FadeOutEvent, fadeOutEvents, 1)
    zox_field_in(AnimationStart, animationStarts, 2)
    zox_field_out(Alpha, alphas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(FadeOutEvent, fadeOutEvents, fadeOutEvent)
        zox_field_i(AnimationStart, animationStarts, animationStart)
        zox_field_o(Alpha, alphas, alpha)
        double animation_time = (time - (animationStart->value)) / fadeOutEvent->value;
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        alpha->value = float_lerp(1, 0, animation_time);
    }
    /*
    zox_field_in(AnimationState, animationTypes, 1)
    zox_field_in(AnimationStart, animationStarts, 2)
    zox_field_in(AnimationLength, animationLengths, 3)
    zox_field_in(AnimationDelay, animationDelays, 4)
    zox_field_out(Alpha, alphas, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(AnimationState, animationTypes, animationType)
        if (animationType->value != zox_animation_fadeout) continue;
        zox_field_i(AnimationStart, animationStarts, animationStart)
        zox_field_i(AnimationLength, animationLengths, animationLength)
        zox_field_i(AnimationDelay, animationDelays, animationDelay)
        zox_field_o(Alpha, alphas, alpha)
        double animation_time = (time - (animationStart->value + animationDelay->value)) / animationLength->value;
        if (animation_time < 0) animation_time = 0;
        else if (animation_time > 1) animation_time = 1;
        alpha->value = float_lerp(1, 0, animation_time);
    }*/
} zox_declare_system(FadeoutSystem)

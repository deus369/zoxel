// when health goes to 0, kill UserLink->value
//  set Dead to 1

void DeathSystem(ecs_iter_t *it) {
    // only update when stat value changes
    // if (!ecs_query_changed(NULL, it)) return;
    zox_iter_world()
    const StatValue *statValues = ecs_field(it, StatValue, 2);
    const UserLink *userLinks = ecs_field(it, UserLink, 3);
    for (int i = 0; i < it->count; i++) {
        const StatValue *statValue = &statValues[i];
        // if (statValue->value > 0) zox_log("   %lu lives\n", it->entities[i])
        if (statValue->value > 0) continue;
        // zox_log("   %lu has no health\n", it->entities[i])
        const UserLink *userLink = &userLinks[i];
        Dead *dead = zox_get_mut(userLink->value, Dead)
        if (dead->value) continue;
        dead->value = 1; // died now
        zox_modified(userLink->value, Dead)
        DiedTime *diedTime = zox_get_mut(userLink->value, DiedTime)
        diedTime->value = zox_current_time;
        zox_modified(userLink->value, DiedTime)
        AnimationState *animationState = zox_get_mut(userLink->value, AnimationState)
        animationState->value = zox_animation_shrink;
        zox_modified(userLink->value, AnimationState)
        AnimationStart *animationStart = zox_get_mut(userLink->value, AnimationStart)
        animationStart->value = zox_current_time;
        zox_modified(userLink->value, AnimationStart)
    }
} zox_declare_system(DeathSystem)

// When health goes to 0, kill UserLink->value
// Set Dead to 1
void DeathSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return; // only update when stat value changes
    zox_iter_world()
    zox_field_in(StatValue, statValues, 1)
    zox_field_in(UserLink, userLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(StatValue, statValues, statValue)
        if (statValue->value > 0) continue;
        zox_field_i_in(UserLink, userLinks, userLink)
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
        zox_log_name(" + [%s] has died", userLink->value)
        // drop item here
    }
} zox_declare_system(DeathSystem)

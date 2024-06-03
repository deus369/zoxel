// When health goes to 0, kill UserLink->value
// Set Dead to 1
void DeathSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return; // only update when stat value changes
    zox_iter_world()
    zox_field_in(StatValue, statValues, 1)
    zox_field_in(UserLink, userLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(StatValue, statValues, statValue)
        if (statValue->value > 0) continue;
        zox_field_i(UserLink, userLinks, userLink)
        Dead *dead = zox_get_mut(userLink->value, Dead)
        if (dead->value) continue;
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
        // died now
        dead->value = 1;
        if (zox_has(userLink->value, DisableMovement)) zox_set(userLink->value, DisableMovement, { 1 })
        const ecs_entity_t last_damager = zox_get_value(userLink->value, LastDamager)
        if (last_damager) {
            zox_log_name(" + [%s] has gained xp", last_damager)
            // add experience to soul stat
            const StatLinks *stats = zox_get(last_damager, StatLinks)
            if (stats->length < 2) continue;
            const ecs_entity_t soul_stat = stats->value[1];
            if (!soul_stat) continue;
            ExperienceValue *experience = zox_get_mut(soul_stat, ExperienceValue)
            ExperienceMax *experience_max = zox_get_mut(soul_stat, ExperienceMax)
            experience->value += 2 + rand() % 6;
            if (experience->value >= experience_max->value) {
                StatValue *soul_level = zox_get_mut(soul_stat, StatValue)
                soul_level->value++;
                experience->value -= experience_max->value;
                experience_max->value = (int) ( experience_max->value * 1.4f);
                zox_log_name(" + [%s] has leveled up", last_damager)
                zox_modified(soul_stat, ExperienceMax)
                zox_modified(soul_stat, StatValue)
            }
            zox_modified(soul_stat, ExperienceValue)
        }
    }
} zox_declare_system(DeathSystem)

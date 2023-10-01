// when health goes to 0, kill UserLink->value
//  set Dead to 1

void DeathSystem(ecs_iter_t *it) {
    // only update when stat value changes
    // if (!ecs_query_changed(NULL, it)) return;
    ecs_world_t *world = it->world;
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
        // todo: add animation for this
        // zox_delete(userLink->value)
        // zox_log("   %lu just died [%f]\n", it->entities[i], time)
    }
} zox_declare_system(DeathSystem)
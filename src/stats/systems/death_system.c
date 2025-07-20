// When health goes to 0, kill UserLink->value
// Set Dead to 1
void DeathSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return; // only update when stat value changes
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(StatValue)
    zox_sys_in(UserLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(StatValue, statValue)
        zox_sys_i(UserLink, userLink)
        if (statValue->value > 0 || zox_gett_value(userLink->value, Dead)) {
            continue;
        }
        // we should just set a dead state here
        zox_muter(userLink->value, Dead, dead)
        dead->value = zox_dirty_trigger;
    }
} zox_declare_system(DeathSystem)
extern double zox_current_time;
const double cleanup_time = 2.0;
// time after death, character will be removed
void DeathCleanSystem(ecs_iter_t *it) {
    // if (!ecs_query_changed(NULL, it)) return; // only update when stat value changes
    zox_iter_world()
    const double time = zox_current_time;
    zox_field_in(Dead, deads, 1)
    zox_field_in(DiedTime, diedTimes, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Dead, deads, dead)
        if (!dead->value) continue;
        zox_field_i(DiedTime, diedTimes, diedTime)
        if (time - diedTime->value >= cleanup_time) zox_delete(it->entities[i])
    }
} zox_declare_system(DeathCleanSystem)

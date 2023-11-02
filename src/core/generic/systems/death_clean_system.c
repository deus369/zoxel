extern double zox_current_time;

// time after death, character will be removed
void DeathCleanSystem(ecs_iter_t *it) {
    const double cleanup_time = 2.0;
    // only update when stat value changes
    // if (!ecs_query_changed(NULL, it)) return;
    ecs_world_t *world = it->world;
    double time = zox_current_time;
    const Dead *deads = ecs_field(it, Dead, 1);
    const DiedTime *diedTimes = ecs_field(it, DiedTime, 2);
    for (int i = 0; i < it->count; i++) {
        const Dead *dead = &deads[i];
        if (!dead->value) continue;
        const DiedTime *diedTime = &diedTimes[i];
        if (time - diedTime->value >= cleanup_time) {
            // zox_log("   %lu just been removed [%f]\n", it->entities[i], time)
            zox_delete(it->entities[i])
        }
    }
} zox_declare_system(DeathCleanSystem)

void StatRegenSystem(ecs_iter_t *it) {
    const float regen_rate = 0.25f;
    const float delta_time = zox_delta_time;
    unsigned char system_updated = 0;
    ecs_world_t *world = it->world;
    const UserLink *userLinks = ecs_field(it, UserLink, 2);
    const StatValueMax *statValueMaxs = ecs_field(it, StatValueMax, 3);
    StatValue *statValues = ecs_field(it, StatValue, 4);
    for (int i = 0; i < it->count; i++) {
        const UserLink *userLink = &userLinks[i];
        if (!userLink->value || !zox_has(userLink->value, Dead)) continue;
        const Dead *dead = zox_get(userLink->value, Dead);
        if (dead->value) continue;
        const StatValueMax *statValueMax = &statValueMaxs[i];
        StatValue *statValue = &statValues[i];
        if (statValue->value < statValueMax->value) {
            statValue->value += delta_time * regen_rate;
            if (statValue->value > statValueMax->value) statValue->value = statValueMax->value;
            system_updated = 1;
            // zox_log(" > new stat value is: %f\n", statValue->value)
        }
    }
#ifndef zoxel_on_windows
    if (!system_updated) ecs_query_skip(it);
#endif
} zox_declare_system(StatRegenSystem)

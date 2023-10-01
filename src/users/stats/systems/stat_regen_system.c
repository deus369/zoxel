void StatRegenSystem(ecs_iter_t *it) {
    float regen_rate = 0.25f;
    float delta_time = zox_delta_time;
    unsigned char changed = 0;
    const UserLink *userLinks = ecs_field(it, UserLink, 1);
    const StatValueMax *statValueMaxs = ecs_field(it, StatValueMax, 2);
    StatValue *statValues = ecs_field(it, StatValue, 3);
    for (int i = 0; i < it->count; i++) {
        const UserLink *userLink = &userLinks[i];
        const Dead *dead = zox_get(userLink->value, Dead);
        if (dead->value) continue;
        const StatValueMax *statValueMax = &statValueMaxs[i];
        StatValue *statValue = &statValues[i];
        if (statValue->value < statValueMax->value) {
            statValue->value += delta_time * regen_rate;
            if (statValue->value > statValueMax->value) statValue->value = statValueMax->value;
            changed = 1;
            // zoxel_log(" > new stat value is: %f\n", statValue->value);
        }
    }
    if (!changed) ecs_query_skip(it);
} zox_declare_system(StatRegenSystem)
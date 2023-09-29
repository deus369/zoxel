void StatRegenSystem(ecs_iter_t *it) {
    float regen_rate = 0.25f;
    float delta_time = zox_delta_time;
    unsigned char changed = 0;
    const StatValueMax *statValueMaxs = ecs_field(it, StatValueMax, 1);
    StatValue *statValues = ecs_field(it, StatValue, 2);
    for (int i = 0; i < it->count; i++) {
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
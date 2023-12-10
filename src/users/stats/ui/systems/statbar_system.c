void StatbarSystem(ecs_iter_t *it) {
    unsigned char system_updated = 0;
    const StatLink *userStatLinks = ecs_field(it, StatLink, 1);
    ElementBar *elementBars = ecs_field(it, ElementBar, 2);
    for (int i = 0; i < it->count; i++) {
        const StatLink *statLink = &userStatLinks[i];
        if (!statLink->value || !zox_has(statLink->value, StatValue)) continue;
        const StatValue *statValue = zox_get(statLink->value, StatValue)
        const StatValueMax *statValueMax = zox_get(statLink->value, StatValueMax)
        ElementBar *elementBar = &elementBars[i];
        const float new_value = statValue->value / statValueMax->value;
        if (elementBar->value != new_value) {
            elementBar->value = new_value;
            system_updated = 1;
        }
    }
#ifndef zoxel_on_windows
    if (!system_updated) ecs_query_skip(it);
#endif
} zox_declare_system(StatbarSystem)

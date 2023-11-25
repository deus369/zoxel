void UserStatbarSystem(ecs_iter_t *it) {
    unsigned char system_updated = 0;
    const UserStatLink *userStatLinks = ecs_field(it, UserStatLink, 1);
    ElementBar *elementBars = ecs_field(it, ElementBar, 2);
    for (int i = 0; i < it->count; i++) {
        const UserStatLink *userStatLink = &userStatLinks[i];
        if (!userStatLink->value) continue;
        ElementBar *elementBar = &elementBars[i];
        const StatValue *statValue = zox_get(userStatLink->value, StatValue)
        const StatValueMax *statValueMax = zox_get(userStatLink->value, StatValueMax)
        const float new_value = statValue->value / statValueMax->value;
        if (elementBar->value != new_value) {
            elementBar->value = new_value;
            system_updated = 1;
        }
    }
#ifndef zoxel_on_windows
    if (!system_updated) ecs_query_skip(it);
#endif
} zox_declare_system(UserStatbarSystem)

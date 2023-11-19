void UserStatbarSystem(ecs_iter_t *it) {
    unsigned char changed = 0;
    const UserStatLink *userStatLinks = ecs_field(it, UserStatLink, 1);
    ElementBar *elementBars = ecs_field(it, ElementBar, 2);
    for (int i = 0; i < it->count; i++) {
        const UserStatLink *userStatLink = &userStatLinks[i];
        if (!userStatLink->value) continue;
        ElementBar *elementBar = &elementBars[i];
        const StatValue *statValue = zox_get(userStatLink->value, StatValue)
        const StatValueMax *statValueMax = zox_get(userStatLink->value, StatValueMax)
        float new_value = statValue->value / statValueMax->value;
        if (elementBar->value != new_value) {
            elementBar->value = new_value;
            changed = 1;
            // zoxel_log("     - new elementBar value is: %f\n", elementBar->value);
        }
    }
    if (!changed) ecs_query_skip(it);
} zox_declare_system(UserStatbarSystem)

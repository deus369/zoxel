void StatbarSystem(ecs_iter_t *it) {
    //unsigned char system_updated = 0;
    zox_field_in(StatLink, statLinks, 1)
    zox_field_out(ElementBar, elementBars, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(StatLink, statLinks, statLink)
        if (!statLink->value || !zox_has(statLink->value, StatValue) || !zox_has(statLink->value, StatValueMax)) continue;
        zox_field_o(ElementBar, elementBars, elementBar)
        const StatValue *statValue = zox_get(statLink->value, StatValue)
        const StatValueMax *statValueMax = zox_get(statLink->value, StatValueMax)
        const float new_value = statValue->value / statValueMax->value;
        if (elementBar->value != new_value) {
            elementBar->value = new_value;
            //system_updated = 1;
        }
    }
#ifndef zoxel_on_windows // ? do i need this still?
    //if (!system_updated) ecs_query_skip(it);
#endif
} zox_declare_system(StatbarSystem)

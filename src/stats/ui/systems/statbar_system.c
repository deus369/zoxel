void StatbarSystem(ecs_iter_t *it) {
    zox_field_in(StatLink, statLinks, 1)
    zox_field_out(ElementBar, elementBars, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(StatLink, statLinks, statLink)
        const ecs_entity_t stat = statLink->value;
        if (!zox_valid(stat) || !zox_has(stat, StatValue) || !zox_has(stat, StatValueMax)) {
            zox_field_e()
            if (!zox_valid(stat)) {
                zox_log_error("stat not found for elementbar [%s]", zox_get_name(e))
            } else {
                zox_log_error("stat was not a state stat [%s] - [%s]", zox_get_name(e), zox_get_name(stat))
            }
            continue;
        }
        zox_field_o(ElementBar, elementBars, elementBar)
        const StatValue *statValue = zox_get(stat, StatValue)
        const StatValueMax *statValueMax = zox_get(stat, StatValueMax)
        const float new_value = statValue->value / statValueMax->value;
        if (elementBar->value != new_value) {
            elementBar->value = new_value;
        }
    }
} zox_declare_system(StatbarSystem)
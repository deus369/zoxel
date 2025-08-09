void StatbarSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(StatLink)
    zox_sys_out(ElementBar)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(StatLink, statLink)
        zox_sys_o(ElementBar, elementBar)
        const ecs_entity_t stat = statLink->value;
        if (!zox_valid(stat)) {
            continue;
        }
        float new_value = elementBar->value;
        if (zox_has(stat, StatState)) {
            zox_geter(stat, StatValue, value)
            zox_geter(stat, StatValueMax, max)
            new_value = value->value / max->value;
        } else if (zox_has(stat, StatLevel)) {
            zox_geter(stat, ExperienceValue, value)
            zox_geter(stat, ExperienceMax, max)
            new_value = value->value / max->value;
        }
        if (elementBar->value != new_value) {
            elementBar->value = new_value;
        }
    }
} zoxd_system(StatbarSystem)
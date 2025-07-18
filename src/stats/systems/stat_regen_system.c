// todo: rework from regen stat, and impact stat value
// do I need a velocity for stats? then regen will add to it? or just add directly..? :O hmm
void StatRegenSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_world()
    zox_field_in(UserLink, userLinks, 1)
    zox_field_in(StatValueMax, statValueMaxs, 2)
    zox_field_out(StatValue, statValues, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserLink, userLinks, userLink)
        zox_field_i(StatValueMax, statValueMaxs, statValueMax)
        zox_field_o(StatValue, statValues, statValue)
        if (!userLink->value || !zox_has(userLink->value, Dead)) {
            continue;
        }
        zox_geter_value(userLink->value, Dead, byte, dead);
        if (dead) {
            continue;
        }
        if (statValue->value < statValueMax->value) {
            statValue->value += delta_time * regen_rate;
            if (statValue->value > statValueMax->value) {
                statValue->value = statValueMax->value;
            }
        }
    }
} zox_declare_system(StatRegenSystem)

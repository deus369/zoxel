// todo: rework from regen stat, and impact stat value
// do I need a velocity for stats? then regen will add to it? or just add directly..? :O hmm
void StatRegenSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UserLink)
    zox_sys_in(StatValueMax)
    zox_sys_out(StatValue)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(UserLink, userLink)
        zox_sys_i(StatValueMax, statValueMax)
        zox_sys_o(StatValue, statValue)
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
} zoxd_system(StatRegenSystem)

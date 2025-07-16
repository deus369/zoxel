// todo: rework from regen stat, and impact stat value
// do I need a velocity for stats? then regen will add to it? or just add directly..? :O hmm
void StatRegenSystem(ecs_iter_t *it) {
    //byte system_updated = 0;
    init_delta_time()
    zox_field_world()
    zox_field_in(UserLink, userLinks, 1)
    zox_field_in(StatValueMax, statValueMaxs, 2)
    zox_field_out(StatValue, statValues, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserLink, userLinks, userLink)
        if (!userLink->value || !zox_has(userLink->value, Dead)) continue;
        const Dead *dead = zox_get(userLink->value, Dead);
        if (dead->value) continue;
        zox_field_i(StatValueMax, statValueMaxs, statValueMax)
        zox_field_o(StatValue, statValues, statValue)
        if (statValue->value < statValueMax->value) {
            statValue->value += delta_time * regen_rate;
            if (statValue->value > statValueMax->value) statValue->value = statValueMax->value;
            //system_updated = 1;
        }
    }
#ifndef zoxel_on_windows
    //if (!system_updated) zox_skip()
#endif
} zox_declare_system(StatRegenSystem)

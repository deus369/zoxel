const double exit_combat_time = 15.0;

void CombatStateSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(LastCombatTime)
    zox_sys_out(InCombat)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(LastCombatTime, lastCombatTime)
        zox_sys_o(InCombat, inCombat)
        if (inCombat->value == zox_combat_trigger_battle) {
            inCombat->value = zox_combat_enter_battle;
        } else if (inCombat->value == zox_combat_enter_battle) {
            inCombat->value = zox_combat_battle;
        } else if (inCombat->value == zox_combat_battle) {
            double time_since_combat = zox_current_time - lastCombatTime->value ;
            if (time_since_combat >= exit_combat_time) {
                inCombat->value = zox_combat_trigger_leaving;
            }
        } else if (inCombat->value == zox_combat_trigger_leaving) {
            inCombat->value = zox_combat_leaving;
        } else if (inCombat->value == zox_combat_leaving) {
            inCombat->value = zox_combat_peace;
        }
    }
} zox_declare_system(CombatStateSystem)
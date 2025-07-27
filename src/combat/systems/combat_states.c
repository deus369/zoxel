const double exit_combat_time = 15.0;

void CombatStateSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(LastCombatTime)
    zox_sys_out(CombatState)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(LastCombatTime, lastCombatTime)
        zox_sys_o(CombatState, combat)
        if (combat->value == zox_combat_trigger_battle) {
            combat->value = zox_combat_enter_battle;
        } else if (combat->value == zox_combat_enter_battle) {
            combat->value = zox_combat_battle;
        } else if (combat->value == zox_combat_battle) {
            double time_since_combat = zox_current_time - lastCombatTime->value ;
            if (time_since_combat >= exit_combat_time) {
                combat->value = zox_combat_trigger_leaving;
            }
        } else if (combat->value == zox_combat_trigger_leaving) {
            combat->value = zox_combat_leaving;
        } else if (combat->value == zox_combat_leaving) {
            combat->value = zox_combat_peace;
        }
    }
} zox_declare_system(CombatStateSystem)
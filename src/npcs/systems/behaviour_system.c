void BehaviourSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CombatState)
    zox_sys_in(DefaultBehaviour)
    zox_sys_out(Behaviour)
    zox_sys_out(MoveForwards)
    zox_sys_out(RotateTowards)
    zox_sys_out(MoveSpeed)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(CombatState, combat)
        zox_sys_i(DefaultBehaviour, defaultBehaviour)
        zox_sys_o(Behaviour, behaviour)
        zox_sys_o(MoveForwards, moveForwards)
        zox_sys_o(RotateTowards, rotateTowards)
        zox_sys_o(MoveSpeed, moveSpeed)
        moveForwards->value = behaviour->value != zox_behaviour_idle;
        rotateTowards->value = behaviour->value != zox_behaviour_idle;
        // only flee if in “wander” mode and not frozen
        if (combat->value == zox_combat_battle) {
            // zox_valid(lastDamager->value)) {
            const byte is_coward = zox_has(e, Coward);
            if (is_coward && behaviour->value != zox_behaviour_flee) {
                behaviour->value = zox_behaviour_flee;
                moveSpeed->value = 8;
                if (is_debug_behaviour) {
                    zox_log("+ has started to flee [%s]", zox_get_name(e))
                }
            } else if (!is_coward && behaviour->value != zox_behaviour_attack) {
                behaviour->value = zox_behaviour_attack;
                moveSpeed->value = 6;
                if (is_debug_behaviour) {
                    zox_log("+ has started to attack [%s]", zox_get_name(e))
                }
            }
        } else if (combat->value == zox_combat_peace) {
            if (behaviour->value != defaultBehaviour->value) {
                behaviour->value = defaultBehaviour->value;
                moveSpeed->value = 3;
                /*if (is_debug_behaviour) {
                    zox_log("+ has started to [%i] [%s]", defaultBehaviour->value, zox_get_name(e))
                }*/
            }
        }
    }
} zoxd_system(BehaviourSystem)

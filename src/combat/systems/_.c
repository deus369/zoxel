#include "death_cleanup.c"
#include "combat_states.c"
zox_increment_system(Dead, zox_dirty_end)

void define_systems_combat(ecs_world_t* world) {
    zox_define_increment_system(Dead)
    zox_system(CombatStateSystem, EcsOnLoad,
            [in] combat.LastCombatTime,
            [out] combat.InCombat)
    zox_system(DeathCleanSystem, EcsOnUpdate,
            [in] combat.Dead,
            [in] DiedTime)
}
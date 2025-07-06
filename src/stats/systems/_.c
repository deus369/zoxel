#include "stat_regen_system.c"
#include "death_system.c"
zox_declare_system_state_event(RealmStats, GenerateRealm, zox_generate_realm_stats, spawn_realm_stats)

void define_systems_stats(ecs_world_t *world) {
    // debuff system here, skills will add debuffs
    zox_system(DeathSystem, EcsOnUpdate, [in] StatValue, [in] UserLink, [none] HealthStat)
    zox_system(StatRegenSystem, EcsOnUpdate, [in] UserLink, [in] StatValueMax, [out] StatValue, [none] StatState)
    zox_define_system_state_event_1(RealmStats, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
}
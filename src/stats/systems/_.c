#include "stat_regen_system.c"
#include "death_system.c"
#include "death_animation_system.c"
#include "level_up_system.c"
#include "experience_system.c"
zox_declare_system_state_event(RealmStats, GenerateRealm, zox_generate_realm_stats, spawn_realm_stats)

void define_systems_stats(ecs_world_t *world) {
    zox_define_system_state_event_1(RealmStats, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    // debuff system here, skills will add debuffs
    zox_system(DeathSystem, EcsOnUpdate,
        [in] StatValue,
        [in] users.UserLink,
        [none] HealthStat)
    zox_system(StatRegenSystem, EcsOnUpdate,
        [in] users.UserLink,
        [in] StatValueMax,
        [out] StatValue,
        [none] StatState)
    zox_system(DeathAnimationSystem, EcsOnUpdate,
        [in] combat.Dead,
        [out] combat.DiedTime,
        [out] physics.DisableMovement,
        [out] animations.AnimationState,
        [out] animations.AnimationStart)
    zox_system_1(ExperienceSystem, EcsOnUpdate,
        [in] combat.Dead,
        [in] combat.LastDamager)
    zox_system_1(LevelUpSystem, EcsOnUpdate,
        [in] users.UserLink,
        [out] stats.StatValue,
        [out] stats.ExperienceValue,
        [out] stats.ExperienceMax,
        [none] StatLevel)
}
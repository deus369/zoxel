#include "melee_system.c"
#include "damage_aura_system.c"
#include "damage_aura_remove_system.c"
#include "dots_system.c"
zox_declare_system_state_event(RealmSkills, GenerateRealm, zox_generate_realm_skills, spawn_realm_skills)

void define_systems_skills(ecs_world_t *world) {
    zox_filter(characters,
            [in] combat.Dead,
            [in] transforms3.Position3D,
            [out] hierarchys.Children,
            [out] stats.DotLinks)
    zox_system_ctx_1(DamageAuraSystem, zox_pip_mainthread, characters,
            [in] users.UserLink,
            [in] SkillActive,
            [in] SkillDamage,
            [in] SkillRange,
            [in] colorz.Color,
            [none] Aura)
    zox_system(DamageAuraRemoveSystem, EcsOnUpdate,
            [in] transforms3.Position3D,
            [out] stats.DotLinks,
            [out] hierarchys.Children)
    zox_system(DotsSystem, EcsOnUpdate,
            [in] users.UserLink,
            [in] users.SpawnerLink,
            [in] SkillDamage,
            [none] Poison)
    zox_define_system_state_event_1(RealmSkills, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
    // todo: make a state system for SkillActive
    zox_system_1(MeleeSystem, zox_pip_mainthread,
            [in] users.UserLink,
            [in] SkillDamage,
            [in] SkillDamageMax,
            [in] SkillRange,
            [in] SkillResourceLink,
            [in] SkillCost,
            [out] SkillActive,
            [none] Melee)
}
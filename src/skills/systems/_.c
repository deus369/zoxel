#include "melee_system.c"
#include "damage_aura_system.c"
#include "damage_aura_remove_system.c"
#include "dots_system.c"
zox_declare_system_state_event(RealmSkills, GenerateRealm, zox_generate_realm_skills, spawn_realm_skills)

void define_systems_skills(ecs_world_t *world) {
    zox_filter(characters, [in] Dead, [in] Position3D, [out] Children, [out] DotLinks)
    zox_system_ctx_1(DamageAuraSystem, zox_pip_mainthread, characters, [in] UserLink, [in] SkillActive, [in] SkillDamage, [in] SkillRange, [in] Color, [none] Aura)
    zox_system(DamageAuraRemoveSystem, EcsOnUpdate, [in] Position3D, [out] DotLinks, [out] Children)
    zox_system(DotsSystem, EcsOnUpdate, [in] UserLink, [in] SpawnerLink, [in] SkillDamage, [none] Poison)
    zox_define_system_state_event_1(RealmSkills, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
    // todo: make a state system for SkillActive
    zox_system_1(MeleeSystem, zox_pip_mainthread, [in] UserLink, [out] SkillActive, [in] SkillDamage, [in] SkillRange, [in] SkillCost, [none] Melee)
}
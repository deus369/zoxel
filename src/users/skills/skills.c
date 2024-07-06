#ifndef zox_mod_skills
#define zox_mod_skills

// remember: when spawned in similar pipeline, it didn't recognize components in a system also in that system, it removed dots straight away because of this..
// sepserate damage logic
// print who kills who
// todo: Aura Skill Entity to remember list of effected characters?
// todo: need ally system
// zox_declare_user_data(Skill)
zox_declare_user_data(Skill)
zox_declare_tag(Melee)
zox_declare_tag(Aura)
zox_declare_tag(Poison)
// zox_component_entity(SkillLink)
zox_component_byte(SkillActive)
zox_component_float(SkillDamage)
zox_component_float(SkillRange)
zox_component_float(SkillCost)
#include "prefabs/prefabs.c"
#include "systems/damage_aura_system.c"
#include "systems/damage_aura_remove_system.c"
#include "systems/dots_system.c"
#include "util/realm_skills.c"
#include "util/character_skills.c"
#include "ui/ui.c"
zox_declare_system_state_event(RealmSkills, GenerateRealm, zox_generate_realm_skills, spawn_realm_skills)

void set_linked_skill(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e) {
    if (!zox_has(user, SkillLinks)) return;
    zox_get_muter(user, SkillLinks, datas)
    if (index >= datas->length) return;
    datas->value[index] = e;
}

zox_begin_module(Skills)
zox_define_tag(Melee)
zox_define_tag(Aura)
zox_define_tag(Poison)
zox_define_user_data(Skill)
zox_define_component_float(SkillDamage)
zox_define_component_float(SkillRange)
zox_define_component_float(SkillCost)
// zox_define_component_entity(SkillLink)
zox_define_component_byte(SkillActive)
zox_filter(characters, [in] Dead, [in] Position3D, [out] Children, [out] DotLinks)
zox_system_ctx_1(DamageAuraSystem, zox_pip_mainthread, characters, [in] UserLink, [in] SkillActive, [in] SkillDamage, [in] SkillRange, [in] Color, [none] Aura)
zox_system(DamageAuraRemoveSystem, EcsOnUpdate, [in] Position3D, [out] DotLinks, [out] Children)
zox_system(DotsSystem, EcsOnUpdate, [in] UserLink, [in] SpawnerLink, [in] SkillDamage, [none] Poison)
zox_import_module(UISkills)
zox_define_system_state_event_1(RealmSkills, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
spawn_prefabs_skills(world);
zoxel_end_module(Skills)

#endif

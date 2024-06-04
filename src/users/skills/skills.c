#ifndef zox_mod_skills
#define zox_mod_skills

// todo: when entering aura, add dot effect onto them
// when leaving, remove
// sepserate damage logic
// print who kills who
// todo: Aura Skill Entity to remember list of effected characters?
// todo: need ally system
// zox_declare_user_data(Skill)
zox_declare_user_data(Skill)
zox_create_user_data_prefabs(Skill, skill, "skill")
zox_declare_tag(Aura)
zox_declare_tag(Poison)
#include "prefabs/prefabs.c"
#include "systems/damage_aura_system.c"
#include "systems/dots_system.c"
#include "util/realm_skills.c"
#include "util/character_skills.c"
#include "ui/ui.c"

zox_begin_module(Skills)
zox_define_user_data(Skill)
zox_define_tag(Aura)
zox_define_tag(Poison)
zox_filter(characters, [in] Dead, [in] Position3D, [out] Children, [out] DotLinks)
zox_system_ctx_1(DamageAuraSystem, main_thread_pipeline, characters, [in] UserLink, [none] Aura)
zox_system(DotsSystem, EcsOnUpdate, [in] UserLink, [in] SpawnerLink, [none] Poison)
zox_import_module(UISkills)
spawn_prefabs_skills(world);
zoxel_end_module(Skills)

#endif

#ifndef zox_skills
#define zox_skills

// todo: when entering aura, add dot effect onto them
// when leaving, remove
// sepserate damage logic
// print who kills who
// todo: Aura Skill Entity to remember list of effected characters?
// todo: need ally system

zox_declare_user_data(Skill)
zox_declare_tag(Aura)
zox_declare_tag(Poison)
#include "prefabs/skill.c"
#include "prefabs/aura.c"
#include "prefabs/poison.c"
#include "systems/damage_aura_system.c"
#include "systems/dots_system.c"

void spawn_prefabs_skills(ecs_world_t *world) {
    spawn_prefab_skill(world);
    spawn_prefab_aura(world);
    spawn_prefab_poison(world);
}

zox_begin_module(Skills)
zox_define_user_data(Skill)
zox_define_tag(Aura)
zox_define_tag(Poison)
zox_filter(characters, [in] Dead, [in] Position3D, [out] Children, [out] DotLinks)
zox_system_ctx_1(DamageAuraSystem, main_thread_pipeline, characters, [in] UserLink, [none] Aura)
zox_system(DotsSystem, EcsOnUpdate, [in] UserLink, [none] Poison)
zoxel_end_module(Skills)

#endif

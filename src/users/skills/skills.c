#ifndef zox_skills
#define zox_skills

// todo: when entering aura, add dot effect onto them
// when leaving, remove
// sepserate damage logic
// print who kills who
// todo: make particle / debuff have poison tag
// todo: make aura another child of character instead
// todo: use UserLink to get character
// todo: for debuff, use UserCreated
// todo: Aura Skill Entity to remember list of effected characters?

zox_declare_user_data(Skill)
zox_declare_tag(Aura)
zox_declare_tag(Poison)
#include "prefabs/skill.c"
#include "prefabs/poison.c"
#include "systems/aoe_damage_system.c"
#include "systems/dots_system.c"

void spawn_prefabs_skills(ecs_world_t *world) {
    spawn_prefab_skill(world);
    spawn_prefab_poison(world);
}

zox_begin_module(Skills)
zox_define_user_data(Skill)
zox_define_tag(Aura)
zox_define_tag(Poison)
zox_filter(characters, [in] Dead, [in] Position3D, [out] Children, [out] DotLinks)
zox_system_ctx_1(AOEDamageSystem, main_thread_pipeline, characters, [in] Position3D, [none] Aura)
zox_system(DotsSystem, EcsOnUpdate, [in] UserLink, [none] Poison)
zoxel_end_module(Skills)

#endif

#ifndef zoxel_skills
#define zoxel_skills

zox_declare_user_data(Skill)
#include "prefabs/skill.c"

zox_begin_module(Skills)
zox_define_user_data(Skill)
spawn_prefab_skill(world);
zoxel_end_module(Skills)

#endif
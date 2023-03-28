#ifndef zoxel_skills
#define zoxel_skills

zoxel_declare_user_data(Skill)
#include "prefabs/skill.c"

zoxel_begin_module(Skills)
zoxel_define_user_data(Skill)
spawn_prefab_skill(world);
zoxel_end_module(Skills)

#endif
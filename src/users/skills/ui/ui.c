#ifndef zox_mod_ui_skills
#define zox_mod_ui_skills

zox_declare_tag(MenuSkills)
#include "prefabs/prefabs.c"

zox_begin_module(UISkills)
zox_define_tag(MenuSkills)
spawn_prefabs_ui_skills(world);
zoxel_end_module(UISkills)

#endif

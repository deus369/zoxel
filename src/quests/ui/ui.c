#ifndef zox_mod_ui_quests
#define zox_mod_ui_quests

zox_declare_tag(MenuQuests)
#include "prefabs/prefabs.c"

zox_begin_module(UIQuests)
zox_define_tag(MenuQuests)
spawn_prefabs_ui_quests(world);
zoxel_end_module(UIQuests)

#endif

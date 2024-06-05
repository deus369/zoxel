#ifndef zox_mod_quests
#define zox_mod_quests

zox_declare_user_data(Quest)
zox_create_user_data_prefabs(Quest, quest, "quest")
#include "prefabs/prefabs.c"
#include "ui/ui.c"
#include "util/realm_quests.c"
#include "util/character_quests.c"

zox_begin_module(Quests)
zox_define_user_data(Quest)
spawn_prefabs_quests(world);
zox_import_module(UIQuests)
zoxel_end_module(Quests)

#endif

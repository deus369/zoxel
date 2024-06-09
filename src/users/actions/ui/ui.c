#ifndef zox_mod_actions_ui
#define zox_mod_actions_ui

zox_declare_user_data(Actionbar)
#include "prefabs/prefabs.c"
#include "util/action_util.c"

zox_begin_module(ActionsUI)
zox_define_user_data(Actionbar)
spawn_prefabs_actions_ui(world);
zoxel_end_module(Actions)

#endif

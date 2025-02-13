#ifndef zox_mod_actions_ui
#define zox_mod_actions_ui

zox_declare_tag(MenuActions)
zox_declare_tag(IconAction)
#include "prefabs/prefabs.c"
#include "util/action_util.c"

zox_begin_module(ActionsUI)
    zox_define_tag(MenuActions)
    zox_define_tag(IconAction)
    spawn_prefabs_actions_ui(world);
zox_end_module(Actions)

#endif

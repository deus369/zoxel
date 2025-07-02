#if !defined(zox_mod_actions) && defined(zox_mod_users)
#define zox_mod_actions

zox_declare_user_data(Action)
#include "prefabs/_.c"
#include "util/character_actions.c"
#include "ui/ui.c"

zox_begin_module(Actions)
    zox_define_user_data(Action)
    spawn_prefabs_actions(world);
    add_hook_spawned_character3D(&spawn_character_actions);
    zox_import_module(ActionsUI)
zox_end_module(Actions)

#endif
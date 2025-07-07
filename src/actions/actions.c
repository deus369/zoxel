#if !defined(zox_mod_actions) && defined(zox_mod_users) && defined(zox_mod_items) && defined(zox_mod_skills)
#define zox_mod_actions

byte test_actions_blocks = 0;
byte test_actions_skills = 0;
zox_declare_user_data(Action)
#include "prefabs/_.c"
#include "util/_.c"
#include "ui/ui.c"

zox_begin_module(Actions)
    zox_define_user_data(Action)
    spawn_prefabs_actions(world);
    add_hook_spawned_character3D(&spawn_character_actions);
    zox_import_module(ActionsUI)
zox_end_module(Actions)

#endif
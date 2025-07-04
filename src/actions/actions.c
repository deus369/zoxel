#if !defined(zox_mod_actions) && defined(zox_mod_users) && defined(zox_mod_items) && defined(zox_mod_skills)
#define zox_mod_actions

zox_declare_user_data(Action)
#include "prefabs/_.c"
#include "util/_.c"
#include "ui/ui.c"

zox_begin_module(Actions)
    zox_define_user_data(Action)
    spawn_prefabs_actions(world);
    add_hook_spawned_character3D(&spawn_character_actions);
    zox_import_module(ActionsUI)
    // set_prefab_debug_label(world, &get_label_player_actions);
zox_end_module(Actions)

#endif
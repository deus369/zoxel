#if !defined(zoxm_actions) && defined(zoxm_users) && defined(zoxm_items) && defined(zoxm_skills)
#define zoxm_actions

byte test_actions_blocks = 0;
byte test_actions_skills = 0;
zox_declare_user_data(Action);
zox_component_byte(ActionIndex);
#include "prefabs/_.c"
#include "util/_.c"
#include "ui/_.c"
#include "systems/_.c"

zox_begin_module(Actions)
    zox_define_user_data(Action);
    zox_define_component(ActionIndex);
    spawn_prefabs_actions(world);
    define_systems_actions(world);
    add_hook_spawned_character3D(&spawn_character_actions);
    zox_import_module(ActionsUI);
zox_end_module(Actions)

#endif
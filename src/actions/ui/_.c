#ifndef zox_mod_actions_ui
#define zox_mod_actions_ui

zox_declare_tag(MenuActions)
zox_declare_tag(IconAction)
#include "prefabs/_.c"
#include "util/_.c"

zox_begin_module(ActionsUI)
    zox_define_tag(MenuActions)
    zox_define_tag(IconAction)
    spawn_prefabs_actions_ui(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_actions,
        .component_id = MenuActions,
        .texture_name = "taskbar_actions"
    });
zox_end_module(Actions)

#endif
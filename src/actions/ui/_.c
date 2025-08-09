#ifndef zoxm_actions_ui
#define zoxm_actions_ui

zox_tag(MenuActions);
zox_tag(IconAction);
#include "prefabs/_.c"
#include "util/_.c"

zox_begin_module(ActionsUI)
    zox_define_tag(MenuActions);
    zox_define_tag(IconAction);
    add_hook_spawn_prefabs(spawn_prefabs_ui_actions);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_actions,
        .component_id = MenuActions,
        .texture_name = "taskbar_actions"
    });
zox_end_module(Actions)

#endif
#ifndef zox_mod_ui_quests
#define zox_mod_ui_quests

zox_declare_tag(MenuQuests)
#include "prefabs/prefabs.c"

zox_begin_module(UIQuests)
    zox_define_tag(MenuQuests)
    spawn_prefabs_ui_quests(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_quests,
        .component_id = MenuQuests,
        .texture_name = "taskbar_quests"
    });
zox_end_module(UIQuests)

#endif

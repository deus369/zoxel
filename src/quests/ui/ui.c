#ifndef zoxm_ui_quests
#define zoxm_ui_quests

zox_tag(MenuQuests);
#include "prefabs/prefabs.c"

zox_begin_module(UIQuests)
    zox_define_tag(MenuQuests);
    add_hook_spawn_prefabs(spawn_prefabs_ui_quests);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_quests,
        .component_id = MenuQuests,
        .texture_name = "taskbar_quests"
    });
zox_end_module(UIQuests)

#endif

#ifndef zoxm_items_ui
#define zoxm_items_ui

zox_tag(MenuItems);
zox_tag(IconItem);
#include "prefabs/_.c"

zox_begin_module(ItemsUI)
    zox_define_tag(MenuItems);
    zox_define_tag(IconItem);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_items,
        .component_id = MenuItems,
        .texture_name = "taskbar_items"
    });
    add_hook_spawn_prefabs(spawn_prefabs_ui_items);
zox_end_module(ItemsUI)

#endif

#ifndef zox_mod_items_ui
#define zox_mod_items_ui

zox_declare_tag(MenuItems)
zox_declare_tag(IconItem)
#include "prefabs/prefabs.c"

zox_begin_module(ItemsUI)
    zox_define_tag(MenuItems)
    zox_define_tag(IconItem)
    spawn_prefabs_items_ui(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_items,
        .component_id = MenuItems,
        .texture_name = "taskbar_items"
    });
zox_end_module(ItemsUI)

#endif

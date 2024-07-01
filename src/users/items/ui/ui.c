#ifndef zox_mod_items_ui
#define zox_mod_items_ui

zox_declare_tag(MenuItems)
zox_declare_tag(ItemIconFrame)
#include "prefabs/prefabs.c"

zox_begin_module(ItemsUI)
zox_define_tag(MenuItems)
zox_define_tag(ItemIconFrame)
spawn_prefabs_items_ui(world);
zoxel_end_module(ItemsUI)

#endif

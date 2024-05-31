#ifndef zox_mod_items
#define zox_mod_items

zox_declare_user_data(Item)
zox_create_user_data_prefabs(Item, item, "item")
#include "prefabs/prefabs.c"
#include "ui/ui.c"
#include "util/realm_items.c"
#include "util/character_items.c"

zox_begin_module(Items)
zox_define_user_data(Item)
zox_import_module(ItemsUI)
spawn_prefabs_items(world);
zoxel_end_module(Items)

#endif

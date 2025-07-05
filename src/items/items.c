#if !defined(zox_mod_items) && defined(zox_mod_users)
#define zox_mod_items

zox_declare_tag(ItemBlock)
zox_declare_user_data(Item)
zox_create_user_data_prefabs(Item, item, "item")
#include "prefabs/_.c"
#include "ui/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Items)
    zox_define_tag(ItemBlock)
    zox_define_user_data(Item)
    zox_define_systems_items(world);
    add_hook_spawned_character3D(&spawn_character_items);
    spawn_prefabs_items(world);
    zox_import_module(ItemsUI)
zox_end_module(Items)

#endif
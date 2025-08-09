#if !defined(zoxm_items) && defined(zoxm_users)
#define zoxm_items

byte test_items_blocks = 0;
zox_tag(ItemBlock);
zoxc_userdata(Item);
zoxf_user_prefabs(Item, item, "item")
#include "prefabs/_.c"
#include "ui/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Items)
    zox_define_tag(ItemBlock);
    zoxd_userdata(Item);
    define_systems_items(world);
    add_hook_spawned_character3D(&spawn_character_items);
    add_hook_spawn_prefabs(spawn_prefabs_items);
    zox_import_module(ItemsUI);
zox_end_module(Items)

#endif
#ifndef zox_mod_items
#define zox_mod_items

zox_declare_user_data(Item)
zox_create_user_data_prefabs(Item, item, "item")
#include "prefabs/prefabs.c"
#include "ui/ui.c"
#include "util/realm_items.c"
#include "util/character_items.c"
zox_declare_system_state_event(RealmItems, GenerateRealm, zox_generate_realm_items, spawn_realm_items)

zox_begin_module(Items)
zox_define_user_data(Item)
zox_import_module(ItemsUI)
spawn_prefabs_items(world);
zox_define_system_state_event_1(RealmItems, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
zoxel_end_module(Items)

#endif

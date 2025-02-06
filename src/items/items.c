#if !defined(zox_mod_items) && defined(zox_mod_users)
#define zox_mod_items

zox_declare_tag(ItemBlock)
zox_declare_user_data(Item)
zox_create_user_data_prefabs(Item, item, "item")
#include "prefabs/prefabs.c"
#include "ui/ui.c"
#include "util/realm_items.c"
#include "util/character_items.c"
zox_declare_system_state_event(RealmItems, GenerateRealm, zox_generate_realm_items, spawn_realm_items)

void set_linked_item(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e) {
    if (!zox_has(user, ItemLinks)) return;
    zox_get_muter(user, ItemLinks, datas)
    if (index >= datas->length) return;
    datas->value[index] = e;
}

zox_begin_module(Items)
    zox_define_tag(ItemBlock)
    zox_define_user_data(Item)
    zox_import_module(ItemsUI)
    spawn_prefabs_items(world);
    zox_define_system_state_event_1(RealmItems, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
zoxel_end_module(Items)

#endif

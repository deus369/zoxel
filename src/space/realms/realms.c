#ifndef zoxel_realms
#define zoxel_realms

zox_declare_tag(Realm)
#include "prefabs/realm.c"
zox_component(RealmLink, ecs_entity_t)

zox_begin_module(Realms)
zox_define_tag(Realm)
zox_define_component(RealmLink)
spawn_prefab_realm(world);
zoxel_end_module(Realms)

#endif
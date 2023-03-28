#ifndef zoxel_realms
#define zoxel_realms

zoxel_declare_tag(Realm)
#include "prefabs/realm.c"
zoxel_component(RealmLink, ecs_entity_t)

zoxel_begin_module(Realms)
zoxel_define_tag(Realm)
zoxel_define_component(RealmLink)
spawn_prefab_realm(world);
zoxel_end_module(Realms)

#endif
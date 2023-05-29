#ifndef zoxel_realms
#define zoxel_realms

// zoxel_component_includes
zox_declare_tag(Realm)
zox_component(RealmLink, ecs_entity_t)
// zoxel_prefab_includes
#include "prefabs/realm.c"
// zoxel_system_includes

zox_begin_module(Realms)
// zoxel_component_defines
zox_define_tag(Realm)
zox_define_component(RealmLink)
// zoxel_prefab_defines
spawn_prefab_realm(world);
// zoxel_system_defines
zoxel_end_module(Realms)

#endif
#ifndef zox_realms
#define zox_realms

// contains all the data used in zox engine
ecs_entity_t prefab_realm;
ecs_entity_t local_realm;
zox_declare_tag(Realm)
zox_component_entity(RealmLink)
#include "prefabs/realm.c"

void initialize_realms(ecs_world_t *world) { }

void spawn_prefabs_realms(ecs_world_t *world) {
    prefab_realm = spawn_prefab_realm(world);
}

zox_begin_module(Realms)
zox_define_tag(Realm)
zox_define_component_entity(RealmLink)
zoxel_end_module(Realms)

#endif

#ifndef zox_mod_realms
#define zox_mod_realms

// todo: we really should fadeoout first before generating realm!
#include "data/generate_realm.c"
zox_declare_tag(Realm)
zox_component_byte(GenerateRealm)
zox_component_entity(RealmLink)
#include "prefabs/prefabs.c"
zox_increment_system_with_reset(GenerateRealm, zox_generate_realm_end)

zox_begin_module(Realms)
zox_define_tag(Realm)
zox_define_component_byte(GenerateRealm)
zox_define_component_entity(RealmLink)
// why is Realm tag not working here??
zox_define_increment_system(GenerateRealm, EcsOnLoad) //, [none] Realm)
zoxel_end_module(Realms)

#endif

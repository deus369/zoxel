#ifndef zoxm_realms
#define zoxm_realms

// todo: we really should fadeoout first before generating realm!
#include "data/generate_realm.c"
zox_tag(Realm);
zoxc_byte(GenerateRealm);
zoxc_entity(RealmLink);
#include "prefabs/prefabs.c"
zox_increment_system_with_reset(GenerateRealm, zox_generate_realm_end);

zox_begin_module(Realms)
    zox_define_tag(Realm);
    zoxd_byte(GenerateRealm);
    zox_define_component_entity(RealmLink);
    zoxd_system_increment(GenerateRealm, [none] Realm);
    add_hook_spawn_prefabs(spawn_prefabs_realms);
zox_end_module(Realms)

#endif
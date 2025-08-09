#if !defined(zoxm_quests) && defined(zoxm_users)
#define zoxm_quests

zoxc_userdata(Quest);
zoxf_user_prefabs(Quest, quest, "quest")
#include "prefabs/_.c"
#include "ui/ui.c"
#include "util/_.c"
zox_declare_system_state_event(RealmQuests, GenerateRealm, zox_generate_realm_quests, spawn_realm_quests)

zox_begin_module(Quests)
    zoxd_userdata(Quest);
    zox_define_system_state_event_1(RealmQuests, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm);
    add_hook_spawned_character3D(&spawn_character_quests);
    add_hook_spawn_prefabs(spawn_prefabs_quests);
    zox_import_module(UIQuests);
zox_end_module(Quests)

#endif

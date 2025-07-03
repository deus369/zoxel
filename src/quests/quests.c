#if !defined(zox_mod_quests) && defined(zox_mod_users)
#define zox_mod_quests

zox_declare_user_data(Quest)
zox_create_user_data_prefabs(Quest, quest, "quest")
#include "prefabs/_.c"
#include "ui/ui.c"
#include "util/_.c"
zox_declare_system_state_event(RealmQuests, GenerateRealm, zox_generate_realm_quests, spawn_realm_quests)

zox_begin_module(Quests)
    zox_define_user_data(Quest)
    zox_define_system_state_event_1(RealmQuests, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
    add_hook_spawned_character3D(&spawn_character_quests);
    spawn_prefabs_quests(world);
    zox_import_module(UIQuests)
    // set_prefab_debug_label(world, &get_label_player_quests);
zox_end_module(Quests)

#endif

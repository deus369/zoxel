#if !defined(zox_mod_achievements) && defined(zox_mod_users)
#define zox_mod_achievements

zox_declare_user_data(Achievement)
// Realm Contains all Achievements
// Save/Load Players progress - per save game
// Toast UI -> show popup at top right when completed - this will trigger steam achievements at bottom right
#include "util/realm_achievements.c"
// Make sure to disable Steam Achievements while testing
zox_declare_system_state_event(RealmAchievements, GenerateRealm, zox_generate_realm_achievements, spawn_realm_achievements)

zox_begin_module(Achievements)
    zox_define_user_data(Achievement)
    zox_define_system_state_event_1(RealmAchievements, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
zoxel_end_module(Achievements)

#endif

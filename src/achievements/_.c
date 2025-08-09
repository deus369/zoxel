#if !defined(zoxm_achievements) && defined(zoxm_users)
#define zoxm_achievements

zoxc_userdata(Achievement);
// Realm Contains all Achievements
// Save/Load Players progress - per save game
// Toast UI -> show popup at top right when completed - this will trigger steam achievements at bottom right
#include "util/realm_achievements.c"
// Make sure to disable Steam Achievements while testing
zox_declare_system_state_event(RealmAchievements, GenerateRealm, zox_generate_realm_achievements, spawn_realm_achievements)

zox_begin_module(Achievements)
    zoxd_userdata(Achievement)
    zox_define_system_state_event_1(RealmAchievements, EcsOnLoad, realms.GenerateRealm, [none] realms.Realm)
zox_end_module(Achievements)

#endif

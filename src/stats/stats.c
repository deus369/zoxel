#if !defined(zox_mod_stats) && defined(zox_mod_users)
#define zox_mod_stats

// todo: Give Health a level too, when it takes damage or heals, it gains xp
// todo: Give HealthRegen a level, when regens more health, it gains xp
// todo: Give Strength a level, when you do actions like lifting, it gains xp (carrying things?)

zox_declare_tag(StatState)
zox_declare_tag(StatRegen)
zox_declare_tag(StatAttribute)
zox_declare_tag(StatLevel)
zox_component_float(StatValue)
zox_component_float(StatValueMax)
zox_component_float(ExperienceValue)
zox_component_float(ExperienceMax)
zox_entities_component(DotLinks)
zox_declare_user_data(Stat)
zox_create_user_data_prefabs(Stat, stat, "stat")
// special stats
zox_declare_tag(HealthStat)
zox_declare_tag(StatSoul)
#include "prefabs/prefabs.c"
#include "util/realm_stats.c"
#include "util/label_util.c"
#include "systems/stat_regen_system.c"
#include "systems/death_system.c"
#include "ui/ui.c"
#include "util/character_stats.c"
zox_declare_system_state_event(RealmStats, GenerateRealm, zox_generate_realm_stats, spawn_realm_stats)

zox_begin_module(Stats)
    zox_define_tag(StatState)
    zox_define_tag(StatRegen)
    zox_define_tag(StatAttribute)
    zox_define_tag(StatLevel)
    zox_define_user_data(Stat)
    zox_define_component_float(StatValue)
    zox_define_component_float(StatValueMax)
    zox_define_component_float(ExperienceValue)
    zox_define_component_float(ExperienceMax)
    zox_define_entities_component(DotLinks)
    // special stats
    zox_define_tag(HealthStat)
    zox_define_tag(StatSoul)
    // debuff system here, skills will add debuffs
    zox_system(DeathSystem, EcsOnUpdate, [in] StatValue, [in] UserLink, [none] HealthStat)
    zox_system(StatRegenSystem, EcsOnUpdate, [in] UserLink, [in] StatValueMax, [out] StatValue, [none] StatState)
    zox_import_module(StatsUI)
    zox_define_system_state_event_1(RealmStats, EcsOnLoad, GenerateRealm) // , [none] realms.Realm)
    spawn_prefabs_stats(world);
    add_hook_spawned_character3D(&spawn_character_stats);
zox_end_module(Stats)

#endif

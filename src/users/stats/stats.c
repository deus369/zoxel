#ifndef zoxel_stats
#define zoxel_stats

// todo:
//      > first create Stat prefab
//      > next child, but keep same name, don't add override to ZoxName property
//      > for GameDebugLabel - use ZoxName component off Stat
// todo: make meta stat same entity, parent of user stat, and share it's name and description
// todo: hover tooltip for healthbar 2D
// todo: why is statvalue showing twice on stats?? oh i get it

// zoxel_component_declares
zox_declare_tag(StateStat)
zox_declare_tag(RegenStat)
zox_declare_tag(AttributeStat)
zox_declare_tag(LevelStat)
zox_declare_tag(HealthStat)
zox_declare_user_data(Stat)
zox_component_float(StatValue)
zox_component_float(StatValueMax)
zox_component_float(ExperienceValue)
zox_component_float(ExperienceMax)
zox_create_user_data_prefabs(Stat, stat, "stat")
// zoxel_prefab_includes
#include "prefabs/stat.c"
#include "prefabs/game_stats.c"
// util
#include "util/label_util.c"
// zoxel_system_includes
#include "systems/stat_regen_system.c"
#include "systems/death_system.c"
// modules
#include "ui/ui.c"

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_stat(world);
    spawn_prefabs_stats_ui(world);
}

zox_begin_module(Stats)
// components
zox_define_tag(StateStat)
zox_define_tag(RegenStat)
zox_define_tag(AttributeStat)
zox_define_tag(LevelStat)
zox_define_tag(HealthStat)
zox_define_user_data(Stat)
zox_define_component_float(StatValue)
zox_define_component_float(StatValueMax)
zox_define_component_float(ExperienceValue)
zox_define_component_float(ExperienceMax)
// systems
// debuff system here, skills will add debuffs
zox_system(DeathCleanSystem, EcsOnUpdate, [in] Dead, [in] DiedTime)
zox_system(DeathSystem, EcsOnUpdate, [none] HealthStat, [in] StatValue, [in] UserLink)
zox_system(StatRegenSystem, EcsPostUpdate, [none] Stat, [in] UserLink, [in] StatValueMax, [out] StatValue) // UserStat
// zox_system(DeathShrinkSystem, EcsOnUpdate, [in] Dead, [in] DiedTime, [out] Scale1D)
// sub modules
zox_import_module(StatsUI)
zoxel_end_module(Stats)

#endif

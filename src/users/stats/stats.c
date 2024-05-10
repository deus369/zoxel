#ifndef zoxel_stats
#define zoxel_stats

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
zox_entities_component(DotLinks)
#include "prefabs/stat.c"
#include "prefabs/game_stats.c"
#include "util/label_util.c"
#include "systems/stat_regen_system.c"
#include "systems/death_system.c"
#include "ui/ui.c"

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_stat(world);
    spawn_prefabs_stats_ui(world);
}

zox_begin_module(Stats)
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
zox_define_entities_component(DotLinks)
// debuff system here, skills will add debuffs
zox_system(DeathCleanSystem, EcsOnUpdate, [in] Dead, [in] DiedTime)
zox_system(DeathSystem, EcsOnUpdate, [in] StatValue, [in] UserLink, [none] HealthStat)
zox_system(StatRegenSystem, EcsOnUpdate, [in] UserLink, [in] StatValueMax, [out] StatValue, [none] Stat)
zox_import_module(StatsUI)
zoxel_end_module(Stats)

#endif

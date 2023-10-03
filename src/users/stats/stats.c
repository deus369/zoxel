#ifndef zoxel_stats
#define zoxel_stats

// zoxel_component_declares
zox_declare_tag(HealthStat)
zox_declare_user_data(Stat)
zox_component(StatValue, float)
zox_component(StatValueMax, float)
zox_create_user_data_prefabs(Stat, stat, "stat")
// zoxel_prefab_includes
#include "prefabs/stat.c"
// zoxel_system_includes
#include "systems/stat_regen_system.c"
#include "systems/death_system.c"
// modules
#include "ui/ui.c"

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_user_stat(world);
    spawn_prefabs_stats_ui(world);
}

zox_begin_module(Stats)
// components
zox_define_tag(HealthStat)
zox_define_user_data(Stat)
zox_define_component(StatValue)
zox_define_component(StatValueMax)
// systems
// debuff system here, skills will add debuffs
zox_system(DeathCleanSystem, EcsOnUpdate, [in] Dead, [in] DiedTime)
zox_system(DeathSystem, EcsOnUpdate, [none] HealthStat, [in] StatValue, [in] UserLink)
zox_system(StatRegenSystem, EcsPostUpdate, [in] UserLink, [in] StatValueMax, [out] StatValue)
// zox_system(DeathShrinkSystem, EcsOnUpdate, [in] Dead, [in] DiedTime, [out] Scale1D)
// sub modules
zox_import_module(StatsUI)
zoxel_end_module(Stats)

#endif
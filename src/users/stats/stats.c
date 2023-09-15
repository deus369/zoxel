#ifndef zoxel_stats
#define zoxel_stats

zox_declare_user_data(Stat)
zox_component(StatValue, float)
zox_component(StatValueMax, float)
zox_create_user_data_prefabs(Stat, stat)    
#include "prefabs/stat.c"
#include "systems/stat_regen_system.c"
#include "ui/ui.c"

void spawn_prefabs_stats(ecs_world_t *world) {
    spawn_prefab_user_stat(world);
    spawn_prefabs_stats_ui(world);
}

zox_begin_module(Stats)
zox_define_user_data(Stat)
zox_define_component(StatValue)
zox_define_component(StatValueMax)
zox_system(StatRegenSystem, EcsOnUpdate, [in] StatValueMax, [out] StatValue)
zox_import_module(StatsUI)
zoxel_end_module(Stats)

#endif
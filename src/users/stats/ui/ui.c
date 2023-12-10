#ifndef zoxel_stats_ui
#define zoxel_stats_ui

#include "systems/statbar_system.c"

void spawn_prefabs_stats_ui(ecs_world_t *world) {
    
}

zox_begin_module(StatsUI)
zox_system(StatbarSystem, EcsPostUpdate, [in] StatLink, [out] ElementBar)
zoxel_end_module(StatsUI)

#endif

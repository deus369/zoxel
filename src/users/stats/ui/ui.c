#ifndef zoxel_stats_ui
#define zoxel_stats_ui

#include "systems/user_statbar_system.c"

void spawn_prefabs_stats_ui(ecs_world_t *world) {
    
}

zox_begin_module(StatsUI)
zox_system(UserStatbarSystem, EcsPostUpdate, [in] UserStatLink, [out] ElementBar)
zoxel_end_module(StatsUI)

#endif
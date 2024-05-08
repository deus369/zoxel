#ifndef zoxel_stats_ui
#define zoxel_stats_ui

zox_declare_tag(Statbar)
#include "prefabs/statbar2D.c"
#include "prefabs/statbar3D.c"
#include "systems/statbar_system.c"

void spawn_prefabs_stats_ui(ecs_world_t *world) {
    spawn_prefab_statbar3D(world);
    spawn_prefab_statbar2D(world);
}

int get_statbars_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Statbar));
}

zox_begin_module(StatsUI)
zox_define_tag(Statbar)
zox_system(StatbarSystem, EcsPostUpdate, [in] StatLink, [out] ElementBar, [none] Statbar)
zoxel_end_module(StatsUI)

#endif

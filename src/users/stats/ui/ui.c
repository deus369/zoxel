#ifndef zox_stats_ui
#define zox_stats_ui

zox_declare_tag(Statbar)
zox_declare_tag(MenuStats)
zox_declare_tag(IconFrameStat)
#include "prefabs/prefabs.c"
#include "systems/statbar_system.c"

int get_statbars_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Statbar));
}

zox_begin_module(StatsUI)
zox_define_tag(Statbar)
zox_define_tag(MenuStats)
zox_define_tag(IconFrameStat)
zox_system(StatbarSystem, EcsPostUpdate, [in] StatLink, [out] ElementBar, [none] Statbar)
spawn_prefabs_ui_stats(world);
zoxel_end_module(StatsUI)

#endif

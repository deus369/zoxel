#ifndef zox_stats_ui
#define zox_stats_ui

zox_declare_tag(Statbar)
zox_declare_tag(StatsMenu)
#include "prefabs/statbar2D.c"
#include "prefabs/statbar3D.c"
#include "prefabs/stats_menu.c"
#include "systems/statbar_system.c"

void spawn_prefabs_stats_ui(ecs_world_t *world) {
    spawn_prefab_statbar3D(world);
    spawn_prefab_statbar2D(world);
    spawn_prefab_stats_menu(world);
}

int get_statbars_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Statbar));
}

zox_begin_module(StatsUI)
zox_define_tag(Statbar)
zox_define_tag(StatsMenu)
zox_system(StatbarSystem, EcsPostUpdate, [in] StatLink, [out] ElementBar, [none] Statbar)
spawn_prefabs_stats_ui(world);
zoxel_end_module(StatsUI)

#endif

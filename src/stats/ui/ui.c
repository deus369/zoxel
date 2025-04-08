#ifndef zox_stats_ui
#define zox_stats_ui

zox_declare_tag(Statbar)
zox_declare_tag(MenuStats)
zox_declare_tag(IconFrameStat)
#include "prefabs/prefabs.c"
#include "systems/statbar_system.c"
#include "systems/stat_text_system.c"

int get_statbars_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Statbar));
}

zox_begin_module(StatsUI)
    zox_define_tag(Statbar)
    zox_define_tag(MenuStats)
    zox_define_tag(IconFrameStat)
    zox_system(StatbarSystem, EcsOnUpdate, [in] StatLink, [out] ElementBar, [none] Statbar)
    zox_system(StatTextSystem, EcsOnUpdate, [in] StatLink, [out] TextData, [out] ZextDirty)
    spawn_prefabs_ui_stats(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_stats,
        .component_id = MenuStats,
        .texture_name = "taskbar_stats"
    });
zox_end_module(StatsUI)

#endif

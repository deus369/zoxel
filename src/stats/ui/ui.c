#ifndef zox_stats_ui
#define zox_stats_ui

zox_declare_tag(Statbar)
zox_declare_tag(MenuStats)
// zox_declare_tag(FrameStat)
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "systems/statbar_system.c"
#include "systems/stat_text_system.c"

zox_begin_module(StatsUI)
    zox_define_tag(Statbar)
    zox_define_tag(MenuStats)
    // zox_define_tag(FrameStat)
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

#ifndef zox_stats_ui
#define zox_stats_ui

zox_declare_tag(Statbar)
zox_declare_tag(MenuStats)
zox_declare_tag(StatsLabel)
#include "prefabs/_.c"
#include "spawn/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(StatsUI)
    zox_define_tag(Statbar)
    zox_define_tag(MenuStats)
    zox_define_tag(StatsLabel)
    define_systems_stats_ui(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_stats,
        .component_id = MenuStats,
        .texture_name = "taskbar_stats"
    });
    add_hook_spawned_character3D(&spawn_character3D_healthbar3D);
    spawn_prefabs_ui_stats(world);
zox_end_module(StatsUI)

#endif
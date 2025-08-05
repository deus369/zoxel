// todo: find a way to add game modules onto game menu - add stats ui on etc
#ifndef zox_mod_game_ui
#define zox_mod_game_ui

// todo: use a byte index instead for menu type
#include "settings/_.c"
#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "spawn/_.c"
#include "systems/_.c"
#include "debug/_.c"

zox_begin_module(GameUI)
    zox_module_dispose(dispose_gameui)
    initialize_hook_taskbar();
    define_components_game_ui(world);
    define_systems_game_ui(world);
    spawn_prefabs_game_ui(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_menu_paused,
        .component_id = MenuPaused,
        .texture_name = "paused"
    });
zox_end_module(GameUI)

#endif
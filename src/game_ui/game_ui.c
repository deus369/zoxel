// todo: find a way to add game modules onto game menu - add stats ui on etc
#ifndef zox_mod_game_ui
#define zox_mod_game_ui

// todo: use a byte index instead for menu type
#include "data/_.c"
#include "components/_.c"
#include "util/_.c"
#include "prefabs/_.c"
#include "systems/_.c"

void dispose_gameui(ecs_world_t *world, void *ctx) {
    dispose_hook_taskbar();
}

zox_begin_module(GameUI)
    zox_module_dispose(dispose_gameui)
    initialize_hook_taskbar();
    zox_define_components_game_ui(world);
    zox_define_systems_game_ui(world);
    spawn_prefabs_game_ui(world);
    add_taskbar_button((hook_taskbar) {
        .spawn = &spawn_player_menu_paused,
        .component_id = MenuPaused,
        .texture_name = "game_icon"
    });
zox_end_module(GameUI)

#endif

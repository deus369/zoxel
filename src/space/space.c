/*  Space:
 *      - this is just unsorted things atm that need refactoring
 *      - alot of functions to spawn the game things
 * */
#if !defined(zox_mod_space) && defined(zox_mod_characters)
#define zox_mod_space

// #define zox_enable_log_start_game
#if defined(zox_enable_log_start_game) && !defined(zox_disable_logs)
    #define zox_log_start_game(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_start_game(msg, ...) { }
#endif

#include "data/settings.c"
zox_component_entity(PlayerPauseEvent)
#include "states/player_state.c"
#include "util/pause_util.c"
#include "prefabs/prefabs.c"
#include "util/game_ui.c"
#include "util/util.c"
#include "tests/aura.c"
#include "systems/systems.c"

zox_begin_module(Space)
    if (headless) {
        return;
    }
    zox_define_component_entity(PlayerPauseEvent)
    define_systems_players2(world);
    add_to_event_game_state((zox_game_event) { &players_game_state });
    spawn_prefabs_players2(world);
    // add_hook_key_down(key_down_test_aura);
zox_end_module(Space)

#endif

// alot of systems here are actually controller ones, player + device + camera / character, or game states like pause system?
// todo: fix block voxes not destroying
// todo: add destruction animation
// todo: hold to destroy
// todo: link to inventory
// todo: pickup items
// todo: arm animations
// todo: hold item animation / spawn item held
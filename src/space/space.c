#if !defined(zox_mod_space) && defined(zox_mod_characters)
#define zox_mod_space
/*  Space:
 *      - this is just unsorted things atm that need refactoring
 *      - alot of functions to spawn the game things
 * */

#include "data/settings.c"
zox_component_entity(PlayerPauseEvent)
#include "states/player_state.c"
#include "prefabs/_.c"
#include "game/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Space)
    if (headless) {
        return;
    }
    zox_define_component_entity(PlayerPauseEvent)
    define_systems_players2(world);
    add_to_event_game_state((zox_game_event) { &players_game_state });
    spawn_prefabs_players2(world);
    // add_hook_key_down(key_down_test_aura);
    // add_hook_key_down(key_down_toggle_streaming);
zox_end_module(Space)

#endif
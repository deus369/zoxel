#if !defined(zox_mod_space) && defined(zox_mod_characters)
#define zox_mod_space
/*  Space:
 *      - this is just unsorted things atm that need refactoring
 *      - alot of functions to spawn the game things
 * */

#include "settings/_.c"
#include "states/player_state.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "game/_.c"
#include "systems/_.c"
#include "debug/_.c"

zox_begin_module(Space)
    define_systems_players2(world);
    spawn_prefabs_players2(world);
    add_to_event_game_state((zox_game_event) { &players_game_state });
    add_hook_on_boot(on_boot_space);
zox_end_module(Space)

#endif
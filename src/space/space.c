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

void toggle_player_death(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_j) {
        zox_log("> player character death toggling")
        if (!zox_valid(local_realm) || !zox_has(local_realm, GameLink)) {
            zox_log_error("no realm (local)")
            return;
        }
        zox_geter(local_realm, GameLink, gameLink)
        if (!zox_valid(gameLink->value)) {
            zox_log_error("realm has no game")
            return;
        }
        zox_geter(gameLink->value, PlayerLinks, players)
        const ecs_entity_t player = players->value[0];
        zox_geter(player, CharacterLink, characterLink)
        if (zox_valid(characterLink->value)) {
            zox_log("- killing player character")
            zox_delete(characterLink->value)
        } else {
            zox_log("+ spawning player character")
            spawn_vox_player_character_in_terrain(world, player);
        }
    }
}

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
    add_hook_key_down(toggle_player_death);
zox_end_module(Space)

#endif
#ifndef zoxm_games
#define zoxm_games

const char *game_name = "zox";
zox_tag(Game);
zoxc_byte(GameState);
zoxc_byte(GameStateTarget);
zoxc_entity(GameLink);
#include "data/_.c"
#include "prefabs/_.c"
#include "util/game_events.c"
#include "systems/_.c"
#include "games2/_.c"
#include "games2/_.c"
#include "debug/_.c"

static inline ecs_entity_t get_player_game(ecs_world_t *world, const ecs_entity_t player) {
    return zox_get_value(player, GameLink);
}

void dispose_games(ecs_world_t *world, void *ctx) {
    (void) world;
    (void) ctx;
    dispose_events_games();
}

zox_begin_module(Games)
    zox_define_tag(Game);
    zox_define_component_byte(GameState);
    zox_define_component_byte(GameStateTarget);
    zox_define_component_entity(GameLink);
    zox_system_1(GameStateSystem, EcsPreStore,
        realms.RealmLink,
        [in] GameStateTarget,
        [out] GameState,
        [none] Game)
    initialize_events_games();
    zox_module_dispose(dispose_games);
    add_hook_terminal_command(process_arguments_games);
    add_hook_spawn_prefabs(spawn_prefabs_games);
zox_end_module(Games)

#endif
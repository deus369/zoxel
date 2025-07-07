#ifndef zox_mod_games
#define zox_mod_games

const char *game_name = "zox";
zox_declare_tag(Game)
zox_component_byte(GameState)
zox_component_byte(GameStateTarget)
zox_component_entity(GameLink)
#include "data/data.c"
#include "prefabs/prefabs.c"
#include "util/game_events.c"
#include "systems/_.c"
#include "games2D/games2D.c"

void initialize_games(ecs_world_t *world) {
    initialize_events_games();
}

void dispose_games(ecs_world_t *world, void *ctx) {
    dispose_events_games();
}

zox_begin_module(Games)
    zox_define_tag(Game)
    zox_define_component_byte(GameState)
    zox_define_component_byte(GameStateTarget)
    zox_define_component_entity(GameLink)
    zox_system_1(GameStateSystem, EcsPreStore, realms.RealmLink, [in] GameStateTarget, [out] GameState, [none] Game)
    zox_module_dispose(dispose_games)
    add_hook_terminal_command(process_arguments_games);
    spawn_prefabs_games(world);
    initialize_games(world);
zox_end_module(Games)

#endif
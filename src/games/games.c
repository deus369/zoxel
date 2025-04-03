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
#include "systems/game_state_system.c"

void initialize_games(ecs_world_t *world) {
    initialize_events_games();
}

void dispose_games(ecs_world_t *world, void *ctx) {
    dispose_events_games();
}

zox_begin_module(Games)
    add_hook_terminal_command(process_arguments_games);
    zox_module_dispose(dispose_games)
    zox_define_tag(Game)
    zox_define_component_byte(GameState)
    zox_define_component_byte(GameStateTarget)
    zox_define_component_entity(GameLink)
    // main thread due to
    zox_system_1(GameStateSystem, EcsPostUpdate, [in] realms.RealmLink, [in] GameStateTarget, [out] GameState, [none] Game)
    spawn_prefabs_games(world);
    initialize_games(world);
zox_end_module(Games)

#endif

#ifndef zox_games
#define zox_games

const char *game_name = "zox";
zox_declare_tag(Game)
zox_component_byte(GameState)
zox_component_byte(GameStateTarget)
zox_component_entity(GameLink)
#include "data/settings.c"
#include "data/rules.c"
#include "data/game_modes.c"
#include "data/game_states.c"
#include "data/zox_game_event.c"
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
    zox_module_dispose(dispose_games)
    zox_define_tag(Game)
    zox_define_component_byte(GameState)
    zox_define_component_byte(GameStateTarget)
    zox_define_component_entity(GameLink)
    // main thread due to
    zox_system_1(GameStateSystem, EcsPostUpdate, [in] realms.RealmLink, [in] GameStateTarget, [out] GameState) // , [none] Game)
    spawn_prefabs_games(world);
    initialize_games(world);
zoxel_end_module(Games)

#endif

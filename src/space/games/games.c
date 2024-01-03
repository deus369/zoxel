#ifndef zoxel_games
#define zoxel_games

// todo: migate this to core and hook off game events
// todo: put game_ui spawns under one game_ui entity

#define zox_game_mode_3D 1
#define zox_game_mode_2D 2
unsigned char zox_game_type;
zox_declare_tag(Game)
zox_component_byte(GameState);
#include "data/zox_game_event.c"
#include "prefabs/game.c"
#include "util/game_states.c"
#include "util/game_events.c"
#include "util/game_util.c"
// #include "systems/play_game_system.c"

void initialize_games(ecs_world_t *world) {
    initialize_events_games();
}

void dispose_games(ecs_world_t *world) {
    dispose_events_games();
}

void spawn_prefabs_games(ecs_world_t *world) {
    spawn_prefab_game(world);
}

zox_begin_module(Games)
zox_define_tag(Game)
zox_define_component(GameState)
// zox_system(PlayGameSystem, EcsPostUpdate, [in] GenericEvent)
zoxel_end_module(Games)

#endif

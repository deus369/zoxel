#ifndef zoxel_games
#define zoxel_games

zox_declare_tag(Game)
zoxel_byte_component(GameState);
#include "prefabs/game.c"
#include "util/game_states.c"
#include "systems/play_game_system.c"

zox_begin_module(Games)
zox_define_tag(Game)
zox_define_component(GameState)
zox_system(PlayGameSystem, EcsPostUpdate, [in] GenericEvent)
spawn_prefab_game(world);
zoxel_end_module(Games)

#endif
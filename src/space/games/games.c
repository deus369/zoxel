#ifndef zoxel_games
#define zoxel_games

zoxel_declare_tag(Game)
zoxel_byte_component(GameState);
#include "prefabs/game.c"
#include "util/game_states.c"
#include "systems/play_game_system.c"

zoxel_begin_module(Games)
zoxel_define_tag(Game)
zoxel_define_component(GameState)
zoxel_system(PlayGameSystem, EcsPostUpdate, [in] GenericEvent)
spawn_prefab_game(world);
zoxel_end_module(Games)

#endif
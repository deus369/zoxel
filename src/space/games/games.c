#ifndef zoxel_games
#define zoxel_games

zox_declare_tag(Game)
zox_component_byte(GameState);
#include "prefabs/game.c"
#include "util/game_states.c"
#include "util/game_util.c"
// #include "systems/play_game_system.c"

void spawn_prefabs_games(ecs_world_t *world) {
    spawn_prefab_game(world);
}

zox_begin_module(Games)
zox_define_tag(Game)
zox_define_component(GameState)
// zox_system(PlayGameSystem, EcsPostUpdate, [in] GenericEvent)
zoxel_end_module(Games)

#endif

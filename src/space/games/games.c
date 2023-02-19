#ifndef zoxel_games
#define zoxel_games

ecs_entity_t local_game;
zoxel_declare_tag(Game)
zoxel_byte_component(GameState);
#include "prefabs/game.c"
#include "util/game_states.c"
#include "systems/play_game_system.c"

//! Games Module
void GamesImport(ecs_world_t *world)
{
    zoxel_module(Games)
    zoxel_define_tag(Game)
    // components
    zoxel_define_component(GameState)
    spawn_prefab_game(world);
    // zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D,
    //    [in] physics.DisableMovement);
    // zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
    zoxel_system(world, PlayGameSystem, EcsPostUpdate, [in] GenericEvent)
}
#endif
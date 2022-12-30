#ifndef zoxel_games
#define zoxel_games

ecs_entity_t local_game;
// Tags
ECS_DECLARE(Game);
// prefabs
#include "prefabs/game.c"
// util
// #include "util/player_character2D.c"
// systems
// #include "systems/player2D_move_system.c"

//! Games Module
void GamesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Games);
    ECS_TAG_DEFINE(world, Game);
    spawn_prefab_game(world);
    // zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D,
    //    [in] physics.DisableMovement);
    // zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
}
#endif
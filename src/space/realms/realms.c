#ifndef zoxel_realms
#define zoxel_realms

ecs_entity_t local_realm;
// Tags
ECS_DECLARE(Realm);
// prefabs
#include "prefabs/realm.c"
// util
// #include "util/player_character2D.c"
// systems
// #include "systems/player2D_move_system.c"

//! Realms Module
void RealmsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Realms);
    ECS_TAG_DEFINE(world, Realm);
    spawn_prefab_realm(world);
    // zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D,
    //    [in] physics.DisableMovement);
    // zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
}
#endif
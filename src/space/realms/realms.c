#ifndef zoxel_realms
#define zoxel_realms

ecs_entity_t local_realm;
zoxel_declare_tag(Realm)
#include "prefabs/realm.c"
// components
zoxel_component(RealmLink, ecs_entity_t);
// #include "util/player_character2D.c"
// #include "systems/player2D_move_system.c"

//! Realms Module
void RealmsImport(ecs_world_t *world)
{
    zoxel_module(Realms)
    zoxel_define_tag(Realm)
    zoxel_define_component(RealmLink)
    spawn_prefab_realm(world);
    // zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D,
    //    [in] physics.DisableMovement);
    // zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard);
}
#endif
#ifndef Zoxel_Characters2D
#define Zoxel_Characters2D
//! Players Module
/**
 * \todo ? idk
*/

// Tags
ECS_DECLARE(Character2D);
// Systems
#include "Systems/BobSpawnSystem.c"
// prefabs
ecs_entity_t character2DPrefab;

void SpawnCharacter2DPrefab(ecs_world_t *world)
{
    character2DPrefab = ecs_new_prefab(world, "Character2D");
    ecs_set(world, character2DPrefab, Position2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Velocity2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Scale2D, { 1 });
    ecs_override(world, character2DPrefab, Position2D);
    ecs_override(world, character2DPrefab, Rotation2D);
    ecs_override(world, character2DPrefab, Scale2D);
    ecs_add(world, character2DPrefab, Brightness);
    ecs_override(world, character2DPrefab, Brightness);
    #ifdef Zoxel_Physics2D
    ecs_set(world, character2DPrefab, Acceleration2D, { { 0, 0 } });
    ecs_set(world, character2DPrefab, Rotation2D, { 0 });
    ecs_set(world, character2DPrefab, Torque2D, { 0 });
    ecs_override(world, character2DPrefab, Velocity2D);
    ecs_override(world, character2DPrefab, Acceleration2D);
    ecs_override(world, character2DPrefab, Torque2D);
    ecs_add(world, character2DPrefab, Frictioned);
    #endif
}

void Characters2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Characters2D);
    ECS_TAG_DEFINE(world, Character2D);
    SpawnCharacter2DPrefab(world);
}
#endif
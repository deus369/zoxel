#ifndef Zoxel_Characters2D
#define Zoxel_Characters2D
//! Players Module

// Tags
ECS_DECLARE(Character2D);
// Systems
#include "Systems/BobSpawnSystem.c"
// prefabs
#include "Prefabs/Character2D.c"

void Characters2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Characters2D);
    ECS_TAG_DEFINE(world, Character2D);
    InitializeCharacter2DPrefab(world);
}
#endif
#ifndef Zoxel_Characters2D
#define Zoxel_Characters2D
//! Players Module

// Tags
ECS_DECLARE(Character2D);
// Components
zoxel_component(Character2DLink, ecs_entity_t);
// Prefabs
#include "Prefabs/Character2D.c"
// Systems
#include "Systems/BobSpawnSystem.c"

ecs_entity_t SpawnCharacter2D(ecs_world_t *world, ecs_entity_t prefab, float2 position)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    ecs_set(world, e, Position2D, { position });
    ecs_set(world, e, Scale1D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, e, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    SpawnGPUMaterial(world, e);
    SpawnGPUTexture(world, e);
    return e;
}

//! A module for 2 dimensional characters.
void Characters2DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Characters2D);
    ECS_TAG_DEFINE(world, Character2D);
    ECS_COMPONENT_DEFINE(world, Character2DLink);
    InitializeCharacter2DPrefab(world);
    // testing, spawn more
    for (int i = 0; i < 100; i++)
    {
        SpawnCharacter2D(world, character2DPrefab, (float2) { -0.5f + (rand() % 100) * 0.2f, -0.5f + (rand() % 100) * 0.2f });
    }
}
#endif
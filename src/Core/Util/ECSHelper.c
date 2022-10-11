#include "../../Flecs/flecs.h"
// Modules
#include "../../Core/Core.h"
#include "../../Transforms2D/Transforms2D.h"
#include "../../Physics2D/Physics2D.h"
#include "../../Rendering/Rendering.h"
#include "../../Textures/Textures.h"

ecs_world_t *world;
ecs_entity_t bobPrefab;
// bob spawning
int bobCount = 0;
const int bobSpawnCount = 10000;
const float positionBounds = 0.1f;
const float velocityBounds = 4.4f;
const float torqueBounds = 8.0f;
const float2 scaleBounds = { 0.1f, 0.6f };
const float2 brightnessBounds = { 0.1f, 0.7f };

//! Initializes prefabs for bob.
void InitializeBobPrefab()
{
    ECS_COMPONENT(world, Position2D);
    ECS_COMPONENT(world, Rotation2D);
    ECS_COMPONENT(world, Velocity2D);
    ECS_COMPONENT(world, Torque2D);
    ECS_COMPONENT(world, Scale2D);
    ECS_COMPONENT(world, Brightness);
    bobPrefab = ecs_new_prefab(world, "");
    ecs_add(world, bobPrefab, Position2D);
    ecs_add(world, bobPrefab, Velocity2D);
    ecs_add(world, bobPrefab, Rotation2D);
    ecs_add(world, bobPrefab, Torque2D);
    ecs_add(world, bobPrefab, Scale2D);
    ecs_add(world, bobPrefab, Brightness);
}

//! Here for now, spawns a one man bobarmy.
void SpawnBobArmy()
{
    ECS_COMPONENT(world, Position2D);
    ECS_COMPONENT(world, Rotation2D);
    ECS_COMPONENT(world, Velocity2D);
    ECS_COMPONENT(world, Torque2D);
    ECS_COMPONENT(world, Scale2D);
    ECS_COMPONENT(world, Brightness);
    // Create a SpaceShip prefab with a Defense component.
    Position2D *position2Ds = malloc(sizeof(Position2D) * bobSpawnCount);
    Velocity2D *velocity2Ds = malloc(sizeof(Velocity2D) * bobSpawnCount);
    // Rotation2D *rotation2Ds = malloc(sizeof(Rotation2D) * bobSpawnCount);
    Torque2D *torque2Ds = malloc(sizeof(Torque2D) * bobSpawnCount);
    Scale2D *scale2Ds = malloc(sizeof(Scale2D) * bobSpawnCount);
    Brightness *brightnesses = malloc(sizeof(Brightness) * bobSpawnCount);
    for (int i = 0; i < bobSpawnCount; i++)
    {
        position2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f)
        };
        velocity2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * velocityBounds - (velocityBounds / 2.0f),
            ((rand() % 101) / 100.0f) * velocityBounds - (velocityBounds / 2.0f)
        };
        torque2Ds[i].value = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
        scale2Ds[i].value = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
        brightnesses[i].value = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
    }
    const ecs_entity_t *bobArmy = ecs_bulk_init(world, &(ecs_bulk_desc_t)
    {
        .count = bobSpawnCount,
        .ids =
        {
            ecs_pair(EcsIsA, bobPrefab),
            ecs_id(Position2D),
            ecs_id(Velocity2D),
            ecs_id(Rotation2D),
            ecs_id(Torque2D),
            ecs_id(Scale2D),
            ecs_id(Brightness)
        },
        /* provide data for each id */
        .data = (void*[])
        {       
            NULL,       /* the pair doesn't have data */
            position2Ds,
            velocity2Ds,
            NULL, // rotation2Ds,
            torque2Ds,
            scale2Ds,
            brightnesses
        }
    });
    bobCount += bobSpawnCount;
}

//! Initialize Flecs ECS and Modules.
void InitializeECS(int argc, char* argv[], bool profiler, bool isRendering)
{
    world = ecs_init_w_args(argc, argv);
    // Initialize Modules
    InitializeTransforms2D(world);
    InitializePhysics2D(world);
    if (isRendering)
    {
        InitializeRendering(world);
    }
    InitializeTextures(world);
    if (profiler)
    {
        ECS_IMPORT(world, FlecsMonitor); 
        ecs_singleton_set(world, EcsRest, {0});
    }
    if (!isRendering)
    {
        ecs_set_threads(world, SDL_GetCPUCount());
    }
    InitializeBobPrefab();
}

void UpdateECS()
{
    ecs_progress(world, deltaTimeSDL);
}

void EndECS()
{
    ecs_fini(world);
}
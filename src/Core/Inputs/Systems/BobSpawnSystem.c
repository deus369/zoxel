#include "../../../Core/Core/Core.h"
#include "../../../Core/Transforms2D/Transforms2D.h"
#include "../../../Core/Rendering/Rendering.h"
#include "../../../Space/Physics2D/Physics2D.h"

bool debugSpawnBobArmy = false;
const bool isFixBulkSpawnCrashing = false;
// A Prefab for Bob
ecs_entity_t bobPrefab;
// Spawn Settings
const int bobSpawnCount = 10000;
const float positionBounds = 0.1f;
const float velocityBounds = 4.4f;
const float torqueBounds = 8.0f;
const float2 scaleBounds = { 0.1f, 0.6f };
const float2 brightnessBounds = { 0.1f, 0.7f };

// forward declarations
void SpawnBobArmy(ecs_world_t *world, ecs_entity_t bobPrefab, int bobSpawnCount);

//! Called in ecs updates
void BobSpawnSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->space.wasPressedThisFrame)
        {
            printf("Spawning Bob Army.\n");
            if (isFixBulkSpawnCrashing)
            {
                debugSpawnBobArmy = true;
            }
            else
            {
                SpawnBobArmy(world, bobPrefab, bobSpawnCount);
            }
        }
    }
}

//! Initializes prefabs for bob.
void InitializeBobSpawnSystem(ecs_world_t *world)
{
    ECS_COMPONENT(world, Position2D);
    ECS_COMPONENT(world, Velocity2D);
    ECS_COMPONENT(world, Acceleration2D);
    ECS_COMPONENT(world, Rotation2D);
    ECS_COMPONENT(world, Torque2D);
    ECS_COMPONENT(world, Scale2D);
    ECS_COMPONENT(world, Brightness);
    bobPrefab = ecs_new_prefab(world, "");
    ecs_add(world, bobPrefab, Position2D);
    ecs_add(world, bobPrefab, Velocity2D);
    ecs_add(world, bobPrefab, Acceleration2D);
    ecs_add(world, bobPrefab, Rotation2D);
    ecs_add(world, bobPrefab, Torque2D);
    ecs_add(world, bobPrefab, Scale2D);
    ecs_add(world, bobPrefab, Brightness);
}

//! Here for now, spawns a one man bobarmy.
void SpawnBobArmy(ecs_world_t *world, ecs_entity_t bobPrefab, int bobSpawnCount)
{
    ECS_COMPONENT(world, Position2D);
    ECS_COMPONENT(world, Velocity2D);
    ECS_COMPONENT(world, Acceleration2D);
    ECS_COMPONENT(world, Rotation2D);
    ECS_COMPONENT(world, Torque2D);
    ECS_COMPONENT(world, Scale2D);
    ECS_COMPONENT(world, Brightness);
    // Create a SpaceShip prefab with a Defense component.
    Position2D *position2Ds = malloc(sizeof(Position2D) * bobSpawnCount);
    Velocity2D *velocity2Ds = malloc(sizeof(Velocity2D) * bobSpawnCount);
    // Rotation2D *rotation2Ds = malloc(sizeof(Rotation2D) * bobSpawnCount);
    // Acceleration2D *acceleration2Ds = malloc(sizeof(Acceleration2D) * bobSpawnCount);
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
            ecs_id(Acceleration2D),
            ecs_id(Rotation2D),
            ecs_id(Torque2D),
            ecs_id(Scale2D),
            ecs_id(Brightness)
        },
        // provide data for each id
        .data = (void*[])
        {       
            NULL,           // Prefab pair, what is it used for?
            position2Ds,
            velocity2Ds,
            NULL,           // Acceleration2D
            NULL,           // Rotation2D
            torque2Ds,
            scale2Ds,
            brightnesses
        }
    });
}

void PrintBobSpawnSystem(ecs_world_t *world)
{
    ECS_COMPONENT(world, Position2D);
    int bobCount = ecs_count(world, Position2D);
    printf("    Bobs Spawned [%i]\n", bobCount);
}

//! Debug used for now, Called in main thread
void SpawnIfSpawn(ecs_world_t *world)
{
    if (debugSpawnBobArmy)
    {
        debugSpawnBobArmy = false;
        SpawnBobArmy(world, bobPrefab, bobSpawnCount);
    }
}
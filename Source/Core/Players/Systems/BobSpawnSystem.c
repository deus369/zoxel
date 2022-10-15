#include "../../../Core/Core/Core.h"
#include "../../../Core/Transforms2D/Transforms2D.h"
#include "../../../Core/Rendering/Rendering.h"
#include "../../../Space/Physics2D/Physics2D.h"

const int bobSpawnCount = 100;
bool debugSpawnBobArmy = false;
const bool isFixBulkSpawnCrashing = false;
ecs_entity_t character2DPrefab;
ecs_entity_t playerCharacter2DPrefab;
ecs_entity_t particle2DPrefab;
extern ecs_entity_t localPlayer;

// forward declarations
void BobSpawnSystem(ecs_iter_t *it);
ECS_SYSTEM_DECLARE(BobSpawnSystem);
void InitializeBobSpawnSystem(ecs_world_t *world);
void BobSpawnSystem(ecs_iter_t *it);
void SpawnBobArmy(ecs_world_t *world, ecs_entity_t character2DPrefab, int bobSpawnCount, float2 offset);
void PrintBobSpawnSystem(ecs_world_t *world);
// void BobArmySpawnFixer(ecs_world_t *world);

//! Initializes prefabs for bob.
void InitializeBobSpawnSystem(ecs_world_t *world)
{
    character2DPrefab = ecs_new_prefab(world, "Character2D");
    ecs_set(world, character2DPrefab, Position2D, { 0, 0 });
    ecs_set(world, character2DPrefab, Velocity2D, { 0, 0 });
    ecs_set(world, character2DPrefab, Acceleration2D, { 0, 0 });
    ecs_set(world, character2DPrefab, Rotation2D, { 0 });
    ecs_set(world, character2DPrefab, Torque2D, { 0 });
    ecs_add(world, character2DPrefab, Scale2D);
    ecs_add(world, character2DPrefab, Brightness);
    ecs_override(world, character2DPrefab, Position2D);
    ecs_override(world, character2DPrefab, Velocity2D);
    ecs_override(world, character2DPrefab, Acceleration2D);
    ecs_override(world, character2DPrefab, Rotation2D);
    ecs_override(world, character2DPrefab, Torque2D);
    ecs_override(world, character2DPrefab, Scale2D);
    ecs_override(world, character2DPrefab, Brightness);
    playerCharacter2DPrefab = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    ecs_add_id(world, playerCharacter2DPrefab, EcsPrefab);
    ecs_set_name(world, playerCharacter2DPrefab, "Player2D");
    ecs_add(world, playerCharacter2DPrefab, Player2D);
    ecs_add(world, playerCharacter2DPrefab, Frictioned);
    ecs_remove(world, playerCharacter2DPrefab, DestroyInTime);
    particle2DPrefab = ecs_new_w_pair(world, EcsIsA, character2DPrefab);
    ecs_add_id(world, particle2DPrefab, EcsPrefab);
    ecs_set_name(world, particle2DPrefab, "Particle2D");
    ecs_add(world, particle2DPrefab, DestroyInTime);
}

//! Spawn a Player character.
ecs_entity_t SpawnPlayer(ecs_world_t *world)
{
    // child prefabs don't seem to inherit tags
    ecs_entity_t bobPlayer = ecs_new_w_pair(world, EcsIsA, playerCharacter2DPrefab);
    ecs_set(world, bobPlayer, Scale2D, { 0.4f + ((rand() % 101) / 100.0f) * 0.2f  });
    ecs_set(world, bobPlayer, Brightness, { 0.8f + ((rand() % 101) / 100.0f) * 0.6f });
    printf("Spawned Player2D [%lu]\n", (long unsigned int) bobPlayer);
    return bobPlayer;
}

//! Called in ecs updates
void BobSpawnSystem(ecs_iter_t *it)
{
    ecs_world_t *world = it->world;
    const Position2D *bobPosition = ecs_get(world, localPlayer, Position2D);
    const Keyboard *keyboards = ecs_field(it, Keyboard, 1);
    for (int i = 0; i < it->count; i++)
    {
        const Keyboard *keyboard = &keyboards[i];
        if (keyboard->space.isPressed) // wasPressedThisFrame)
        {
            // printf("Firing the Bob Army.\n");
            if (isFixBulkSpawnCrashing)
            {
                debugSpawnBobArmy = true;
            }
            else
            {
                SpawnBobArmy(world, character2DPrefab, bobSpawnCount, bobPosition->value);
            }
        }
        else if (keyboard->p.wasPressedThisFrame)
        {
            printf("[Printing Debug]\n");
            PrintBobSpawnSystem(world);
            PrintKeyboard(world);
        }
        else if (keyboard->z.wasPressedThisFrame)
        {
            printf("Spawning new Player.\n");
            SpawnPlayer(world);
        }
    }
}

//! Here for now, spawns a one man bobarmy.
void SpawnBobArmy(ecs_world_t *world, ecs_entity_t character2DPrefab, int bobSpawnCount, float2 bobPosition)
{
    float2 positionBounds = { 0.1f, 0.5f };
    const float2 velocityBounds = { 0.2f, 12.4f };
    const float torqueBounds = 12.0f;
    const float2 scaleBounds = { 0.1f, 0.23f };
    const float2 brightnessBounds = { 0.1f, 0.4f };
    const double2 lifeTime = { 0.5f, 8.0f };
    // Create a SpaceShip prefab with a Defense component.
    Position2D *position2Ds = malloc(sizeof(Position2D) * bobSpawnCount);
    Velocity2D *velocity2Ds = malloc(sizeof(Velocity2D) * bobSpawnCount);
    // Rotation2D *rotation2Ds = malloc(sizeof(Rotation2D) * bobSpawnCount);
    // Acceleration2D *acceleration2Ds = malloc(sizeof(Acceleration2D) * bobSpawnCount);
    Torque2D *torque2Ds = malloc(sizeof(Torque2D) * bobSpawnCount);
    Scale2D *scale2Ds = malloc(sizeof(Scale2D) * bobSpawnCount);
    Brightness *brightnesses = malloc(sizeof(Brightness) * bobSpawnCount);
    DestroyInTime *destroyInTimes = malloc(sizeof(DestroyInTime) * bobSpawnCount);
    for (int i = 0; i < bobSpawnCount; i++)
    {
        position2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * positionBounds.y - (positionBounds.y / 2.0f)
        };
        if (position2Ds[i].value.x < - positionBounds.x)
        {
            position2Ds[i].value.x = - positionBounds.x;
        }
        else if (position2Ds[i].value.x > positionBounds.x)
        {
            position2Ds[i].value.x = positionBounds.x;
        }
        if (position2Ds[i].value.y < - positionBounds.x)
        {
            position2Ds[i].value.y = - positionBounds.x;
        }
        else if (position2Ds[i].value.y > positionBounds.x)
        {
            position2Ds[i].value.y = positionBounds.x;
        }
        position2Ds[i].value.x += bobPosition.x;
        position2Ds[i].value.y += bobPosition.y;
        velocity2Ds[i].value = (float2) {
            ((rand() % 101) / 100.0f) * velocityBounds.y - (velocityBounds.y / 2.0f),
            ((rand() % 101) / 100.0f) * velocityBounds.y - (velocityBounds.y / 2.0f)
        };
        if (velocity2Ds[i].value.x < - velocityBounds.x)
        {
            velocity2Ds[i].value.x = - velocityBounds.x;
        }
        else if (velocity2Ds[i].value.x > velocityBounds.x)
        {
            velocity2Ds[i].value.x = velocityBounds.x;
        }
        if (velocity2Ds[i].value.y < - velocityBounds.x)
        {
            velocity2Ds[i].value.y = - velocityBounds.x;
        }
        else if (velocity2Ds[i].value.y > velocityBounds.x)
        {
            velocity2Ds[i].value.y = velocityBounds.x;
        }
        torque2Ds[i].value = ((rand() % 101) / 100.0f) * torqueBounds - (torqueBounds / 2.0f);
        scale2Ds[i].value = scaleBounds.x + ((rand() % 101) / 100.0f) * (scaleBounds.y - scaleBounds.x);
        brightnesses[i].value = brightnessBounds.x + ((rand() % 101) / 100.0f) * (brightnessBounds.y - brightnessBounds.x);
        destroyInTimes[i].value = lifeTime.x + ((rand() % 101) / 100.0f) *  (lifeTime.y - lifeTime.x);
    }
    const ecs_entity_t *bobArmy = ecs_bulk_init(world, &(ecs_bulk_desc_t)
    {
        .count = bobSpawnCount,
        .ids =
        {
            ecs_pair(EcsIsA, particle2DPrefab),
            ecs_id(Position2D),
            ecs_id(Velocity2D),
            ecs_id(Acceleration2D),
            ecs_id(Rotation2D),
            ecs_id(Torque2D),
            ecs_id(Scale2D),
            ecs_id(Brightness),
            ecs_id(DestroyInTime)
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
            brightnesses,
            destroyInTimes
        }
    });
}

int GetBobCount()
{
    return ecs_count(world, Position2D);
}

void PrintBobSpawnSystem(ecs_world_t *world)
{
    printf("    Bobs Spawned [%i]\n", GetBobCount());
}

//! Debug used for now, Called in main thread
/*void BobArmySpawnFixer(ecs_world_t *world)
{
    if (debugSpawnBobArmy)
    {
        debugSpawnBobArmy = false;
        SpawnBobArmy(world, character2DPrefab, bobSpawnCount);
    }
}*/

    // ECS_ENTITY(world, character2DPrefab, Position2D, OVERRIDE | Position2D);

    // ecs_set_id(world, character2DPrefab, ECS_OVERRIDE | ecs_id(Position2D), sizeof(Position2D), &(Position2D){ 0, 0 });
    
    // ecs_set(world, character2DPrefab, Position2D, ECS_OVERRIDE | Position2D);

    /*ECS_ENTITY(world, character2DPrefab, Velocity2D, OVERRIDE | Velocity2D);
    ECS_ENTITY(world, character2DPrefab, Acceleration2D, OVERRIDE | Acceleration2D);
    ECS_ENTITY(world, character2DPrefab, Rotation2D, OVERRIDE | Rotation2D);
    ECS_ENTITY(world, character2DPrefab, Torque2D, OVERRIDE | Torque2D);
    ECS_ENTITY(world, character2DPrefab, Scale2D, OVERRIDE | Scale2D);
    ECS_ENTITY(world, character2DPrefab, Brightness, OVERRIDE | Brightness);*/

    // ecs_entity_t bobPlayer = ecs_new_w_pair(world, EcsChildOf, playerCharacter2DPrefab);
    /*har *playerName = strcat("Player (Instance) [%lu]", bobPlayer);
    ecs_set_name(world, bobPlayer, playerName);
    free(playerName);*/
// Add this here until Automatic Override works https://flecs.docsforge.com/master/manual/#automatic-overriding
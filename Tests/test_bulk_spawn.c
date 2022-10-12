//! This script tests bulk spawning inside a system!

// build line
// cc -std=c99 -o test_bulk_spawn src/Imports/Flecs/flecs.c Tests/test_bulk_spawn.c; ./test_bulk_spawn;
#include "../src/Imports/Flecs/flecs.h"
#include "stdlib.h"
#include "stdio.h"

const bool isFixCrash = false;
// components
typedef struct
{
    float a;    // no empty structs? :(
} Spawner;
typedef struct
{
    float x, y;
} Position2D;
// forward declares
ECS_COMPONENT_DECLARE(Spawner);
ECS_COMPONENT_DECLARE(Position2D);
void SpawnSystem(ecs_iter_t *it);
// prefab and spawn settings
ecs_entity_t bobPrefab;
float positionBounds = 1;

int main(int argc, char *argv[]) 
{
    // initialize world
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    // initialize components
    ECS_COMPONENT_DEFINE(world, Spawner);
    ECS_COMPONENT_DEFINE(world, Position2D);
    // prefab spawn
    bobPrefab = ecs_new_prefab(world, "");
    ecs_add(world, bobPrefab, Position2D);
    // add system
    ECS_SYSTEM(world, SpawnSystem, EcsOnUpdate, Spawner);
    // add spawner
    ecs_entity_t e1 = ecs_new_entity(world, "lespawner");
    ecs_add(world, e1, Spawner);
    // progress once
    ecs_progress(world, 0.1);
    int bobCount1 = ecs_count(world, Position2D);
    printf("Spawned 1 [%i]\n", bobCount1);
    // progress once more
    ecs_progress(world, 0.2);
    int bobCount2 = ecs_count(world, Position2D);
    printf("Spawned 2 [%i]\n", bobCount2);
    // le end
    return ecs_fini(world);
}

void SpawnSystem(ecs_iter_t *it)
{
    int spawnCount = 5;
    printf("Spawning System; spawners: [%i] x [%i]\n", it->count, spawnCount);
    for (int i = 0; i < it->count; i ++)
    {
        // Create a SpaceShip prefab with a Defense component.
        Position2D *position2Ds = malloc(sizeof(Position2D) * spawnCount);
        for (int i = 0; i < spawnCount; i++)
        {
            position2Ds[i].x = ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f);
            position2Ds[i].y = ((rand() % 101) / 100.0f) * positionBounds - (positionBounds / 2.0f);
        }
        // This line crashes it!
        if (!isFixCrash)
        {
            const ecs_entity_t *bobArmy = ecs_bulk_init(it->world, &(ecs_bulk_desc_t)
            {
                .count = spawnCount,
                .ids =
                {
                    ecs_pair(EcsIsA, bobPrefab),
                    ecs_id(Position2D)
                },
                // provide data for each id
                .data = (void*[])
                {       
                    NULL,           // Prefab pair, what is it used for?
                    position2Ds
                }
            });
        }
    }
}
//! This script tests spawning from a prefab in a loop.

// Build:
// cc -std=c99 -D_DEFAULT_SOURCE -o tests/flecs/test_spawn_component imports/flecs.c tests/flecs/test_spawn_component.c; ./tests/flecs/test_spawn_component;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct {
    int value;
} Material;
ECS_COMPONENT_DECLARE(Material);

int main(int argc, char *argv[]) 
{
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    ECS_COMPONENT_DEFINE(world, Material);
    // prefab
    ecs_entity_t prefab = ecs_new_prefab(world, "character2D_prefab");
    ecs_add_id(world, prefab, ecs_id(Material));
    ecs_override_id(world, prefab, ecs_id(Material));
    ecs_entity_t first_entity;
    for (int i = 0; i < 2; i++)
    {
        ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
        ecs_set(world, e, Material, { rand() % 1000 });
        if (i == 0)
        {
            first_entity = e;
            printf("Inside Loop - Material [%lu] : %i\n", (long int) first_entity, ecs_get(world, first_entity, Material)->value);
        }
    }
    printf("Outside Loop - Material [%lu] : %i\n", (long int) first_entity, ecs_get(world, first_entity, Material)->value);
    
    printf("RESULT: SUCCESS\n");
    return 0;
}
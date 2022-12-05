//! This script tests ecs_get_mut

// build line
// cc -std=c99 -o test_ecs_get_mut src/imports/flecs.c tests/test_ecs_get_mut.c; ./test_ecs_get_mut;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct
{
    bool value;
} IsAwesome;

ECS_COMPONENT_DECLARE(IsAwesome);

int main(int argc, char *argv[]) 
{
    // initialize world
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    // initialize components
    ECS_COMPONENT(world, IsAwesome);

    // add spawner
    ecs_entity_t awesomeEntity = ecs_new_entity(world, "awesomeone");
    ecs_add(world, awesomeEntity, IsAwesome);

    // progress once
    ecs_progress(world, 0.1);
    printf("Spawned 1 [%i]\n", ecs_count(world, IsAwesome));
    
    IsAwesome *isAwesome = ecs_get_mut(world, awesomeEntity, IsAwesome);
    isAwesome->value = true;
    ecs_modified(world, awesomeEntity, IsAwesome);

    // progress twonce
    ecs_progress(world, 0.1);
    printf("Spawned 2 [%i]\n", ecs_count(world, IsAwesome));

    // le end
    printf("RESULT: SUCCESS\n");
    return ecs_fini(world);
}
//! This script tests using tags accross 2 seperate modules.

// Build:
// cc -std=c99 -D_DEFAULT_SOURCE -o tests/flecs/test_tags_and_modules imports/flecs.c tests/flecs/test_tags_and_modules.c; ./tests/flecs/test_tags_and_modules;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

// Tags
ECS_DECLARE(TagA);

void TestSystem(ecs_iter_t *it) { } ECS_SYSTEM_DECLARE(TestSystem);

void ModuleAImport(ecs_world_t *world)
{
    printf("ModuleA Importing. Defining TagA.\n");
    ECS_MODULE(world, ModuleA);
    ECS_TAG_DEFINE(world, TagA);
}

void ModuleBImport(ecs_world_t *world)
{
    printf("ModuleB Importing. Using TagA.\n");
    ECS_MODULE(world, ModuleB);
    ECS_SYSTEM_DEFINE(world, TestSystem, EcsOnUpdate, [none] module.a.TagA);
}

int main(int argc, char *argv[]) 
{
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    ECS_IMPORT(world, ModuleA);
    ECS_IMPORT(world, ModuleB);
    printf("RESULT: SUCCESS\n");
    return 0;
}
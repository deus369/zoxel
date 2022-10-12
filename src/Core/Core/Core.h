#ifndef Zoxel_Core
#define Zoxel_Core

#include "Components/ID.c"
#include "Data/float2.c"

ECS_COMPONENT_DECLARE(ID);

void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_COMPONENT_DEFINE(world, ID);
    // ECS_SYSTEM(world, Velocity2DSystem, EcsOnUpdate, Position2D, Velocity2D);
}

#endif
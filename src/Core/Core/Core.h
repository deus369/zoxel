#ifndef Zoxel_Core
#define Zoxel_Core

// Data
#include "Data/float2.c"
#include "Data/float3.c"
#include "Data/float4.c"
#include "Data/float4x4.c"
#include "Data/double2.c"
// Components
#include "Components/ID.c"
// Util
#include "Util/TimeHelper.c"

void CoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, Core);
    ECS_COMPONENT_DEFINE(world, ID);
    // ECS_SYSTEM(world, Velocity2DSystem, EcsOnUpdate, Position2D, Velocity2D);
}

#endif
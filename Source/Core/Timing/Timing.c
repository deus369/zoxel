#ifndef Zoxel_Timing
#define Zoxel_Timing
//! Timing Module.

#include "Components/DestroyInTime.c"
#include "Systems/DestroyInTimeSystem.c"

void TimingImport(ecs_world_t *world)
{
    ECS_MODULE(world, Timing);
    ECS_COMPONENT_DEFINE(world, DestroyInTime);
    ECS_SYSTEM_DEFINE(world, DestroyInTimeSystem, EcsOnUpdate, [out] DestroyInTime);
}
#endif
#ifndef Zoxel_Timing
#define Zoxel_Timing

// Components
#include "Components/DestroyInTime.c"
// Systems
#include "Systems/DestroyInTimeSystem.c"

//! Timing Module.
void TimingImport(ecs_world_t *world)
{
    ECS_MODULE(world, Timing);
    ECS_COMPONENT_DEFINE(world, DestroyInTime);
    ZOXEL_SYSTEM_MULTITHREADED(world, DestroyInTimeSystem, EcsOnUpdate, [out] DestroyInTime);
}
#endif
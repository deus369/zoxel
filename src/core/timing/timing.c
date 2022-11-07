#ifndef zoxel_timing
#define zoxel_timing

// components
//! Used to set the brightness of an entity.
zoxel_component(DestroyInTime, double);
// systems
#include "systems/DestroyInTimeSystem.c"

//! timing Module.
void TimingImport(ecs_world_t *world)
{
    ECS_MODULE(world, Timing);
    ECS_COMPONENT_DEFINE(world, DestroyInTime);
    zoxel_system(world, DestroyInTimeSystem, EcsOnUpdate, [out] DestroyInTime);
}
#endif
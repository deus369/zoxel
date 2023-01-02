#ifndef zoxel_timing
#define zoxel_timing

zoxel_component(DestroyInTime, double)      //! Used to set the brightness of an entity.
#include "systems/DestroyInTimeSystem.c"

//! timing Module.
void TimingImport(ecs_world_t *world)
{
    zoxel_module(Timing)
    zoxel_define_component(DestroyInTime)
    zoxel_system(world, DestroyInTimeSystem, EcsOnUpdate, [out] DestroyInTime);
}
#endif
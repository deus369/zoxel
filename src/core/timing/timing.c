#ifndef zoxel_timing
#define zoxel_timing

zoxel_component(DestroyInTime, double)
#include "util/time_macros.c"
#include "util/time_util.c"
#include "systems/destroy_in_time_system.c"

zoxel_begin_module(Timing)
zoxel_define_component(DestroyInTime)
zoxel_system(DestroyInTimeSystem, EcsOnUpdate, [out] DestroyInTime)
initialize_time();
zoxel_end_module(Timing)

#endif
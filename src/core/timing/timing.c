#ifndef zoxel_timing
#define zoxel_timing

zox_component(DestroyInTime, double)
#include "util/time_macros.c"
#include "util/time_util.c"
#include "systems/destroy_in_time_system.c"

zox_begin_module(Timing)
zox_define_component(DestroyInTime)
zox_system(DestroyInTimeSystem, EcsOnUpdate, [out] DestroyInTime)
initialize_time();
zoxel_end_module(Timing)

#endif
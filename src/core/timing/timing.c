#ifndef zoxel_timing
#define zoxel_timing

zox_component_double(DestroyInTime)
#include "util/time_macros.c"
#include "util/time_util.c"
#include "systems/destroy_in_time_system.c"

zox_begin_module(Timing)
zox_define_component_double(DestroyInTime)
zox_system(DestroyInTimeSystem, EcsPreStore, [out] DestroyInTime)
// zox_system_1(DestroyInTimeSystem, main_thread_pipeline, [out] DestroyInTime)
initialize_time();
zoxel_end_module(Timing)

#endif

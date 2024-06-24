#ifndef zox_mod_timing
#define zox_mod_timing

#include <time.h>
#include "data/settings.c"
zox_component_double(DestroyInTime)
#include "util/time_macros.c"
#include "util/time_util.c"
#include "systems/destroy_in_time_system.c"

zox_begin_module(Timing)
zox_define_component_double(DestroyInTime)
zox_system(DestroyInTimeSystem, EcsPreStore, [out] DestroyInTime)
initialize_time();
zoxel_end_module(Timing)

#endif

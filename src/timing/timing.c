#ifndef zox_mod_timing
#define zox_mod_timing

#include <time.h>
#include "data/settings.c"
zox_component_double(DestroyInTime)
zox_component_double(TimerTime)
zox_component_double(TimerRate)
zox_component_byte(TimerState)
#include "util/time_macros.c"
#include "util/time_util.c"
#include "systems/destroy_in_time_system.c"
#include "systems/timer_system.c"

zox_begin_module(Timing)
    zox_define_component_double(DestroyInTime)
    zox_define_component_double(TimerTime)
    zox_define_component_double(TimerRate)
    zox_define_component_byte(TimerState)
    zox_system(DestroyInTimeSystem, EcsPostUpdate, [out] DestroyInTime)
    zox_system(TimerSystem, EcsPostUpdate, [in] TimerRate, [out] TimerState, [out] TimerTime)
    add_to_post_update_loop(iterate_time);
    initialize_time();
zoxel_end_module(Timing)

#endif

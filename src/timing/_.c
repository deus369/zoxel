#ifndef zox_mod_time
#define zox_mod_time

#include "data/settings.c"
zox_component_double(DestroyInTime)
zox_component_double(TimerTime)
zox_component_double(TimerRate)
zox_component_byte(TimerState)
#include "macros/_.c"
#include "util/_.c"
#include "systems/destroy_in_time_system.c"
#include "systems/timer_system.c"

zox_begin_module(Timing)
    zox_define_component_double(DestroyInTime)
    zox_define_component_double(TimerTime)
    zox_define_component_double(TimerRate)
    zox_define_component_byte(TimerState)
    zox_system(TimerSystem, EcsPostUpdate,
        [in] TimerRate,
        [out] TimerState,
        [out] TimerTime)
    zox_system_1(DestroyInTimeSystem, EcsOnStore,
        [out] timing.DestroyInTime)
    add_to_post_update_loop(iterate_time);
    initialize_time();
zox_end_module(Timing)

#endif
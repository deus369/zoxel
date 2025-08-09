#ifndef zoxm_time
#define zoxm_time

#include "data/settings.c"
zoxc_double(DestroyInTime);
zoxc_double(TimerTime);
zoxc_double(TimerRate);
zoxc_byte(TimerState);
#include "macros/_.c"
#include "util/_.c"
#include "systems/destroy_in_time_system.c"
#include "systems/timer_system.c"

zox_begin_module(Timing)
    zox_define_component_double(DestroyInTime);
    zox_define_component_double(TimerTime);
    zox_define_component_double(TimerRate);
    zox_define_component_byte(TimerState);
    zox_system(TimerSystem, EcsOnUpdate,
        [in] TimerRate,
        [out] TimerState,
        [out] TimerTime);
    zox_system_1(DestroyInTimeSystem, zoxp_destroy,
        [out] timing.DestroyInTime);
    initialize_time();
    add_to_post_update_loop(iterate_time);
    add_to_post_update_loop(iterate_time_system);
zox_end_module(Timing)

#endif
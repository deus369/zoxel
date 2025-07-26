void TimerSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_begin()
    zox_sys_in(TimerRate)
    zox_sys_out(TimerState)
    zox_sys_out(TimerTime)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TimerRate, timerRate)
        zox_sys_o(TimerState, timerState)
        zox_sys_o(TimerTime, timerTime)
        timerState->value = 0;
        if (timerTime->value == 0) {
            timerTime->value = timerRate->value;
        } else {
            timerTime->value -= delta_time;
            if (timerTime->value <= 0) {
                timerTime->value = 0;
                timerState->value = 1;
            }
        }
    }
} zox_declare_system(TimerSystem)

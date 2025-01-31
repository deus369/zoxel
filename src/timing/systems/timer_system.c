void TimerSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_in(TimerRate, timerRates, 1)
    zox_field_out(TimerState, timerStates, 2)
    zox_field_out(TimerTime, timerTimes, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(TimerRate, timerRates, timerRate)
        zox_field_o(TimerState, timerStates, timerState)
        zox_field_o(TimerTime, timerTimes, timerTime)
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

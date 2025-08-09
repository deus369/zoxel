extern double zox_delta_time;

void TimedEventSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TimedEvent)
    zox_sys_in(EventInput)
    zox_sys_out(EventTime)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(TimedEvent, timedEvent)
        zox_sys_i(EventInput, eventInput)
        zox_sys_o(EventTime, eventTime)
        eventTime->value -= zox_delta_time;
        if (eventTime->value <= 0) {
            if (timedEvent->value) {
                (*timedEvent->value)(world, eventInput->value);
            }
            zox_delete(e)
        }
    }
} zoxd_system(TimedEventSystem)
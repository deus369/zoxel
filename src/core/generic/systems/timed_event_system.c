extern double zox_delta_time;

void TimedEventSystem(ecs_iter_t *it) {
    zox_iter_world()
    const double delta = zox_delta_time;
    zox_field_in(TimedEvent, timedEvents, 1)
    zox_field_in(EventInput, eventInputs, 2)
    zox_field_out(EventTime, eventTimes, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(EventTime, eventTimes, eventTime)
        eventTime->value -= delta;
        if (eventTime->value <= 0) {
            zox_field_e()
            zox_field_i_in(TimedEvent, timedEvents, timedEvent)
            zox_field_i_in(EventInput, eventInputs, eventInput)
            if (timedEvent->value) (*timedEvent->value)(world, eventInput->value);
            zox_delete(e)
        }
    }
} zox_declare_system(TimedEventSystem)

// todo: use prefab_event_delay

ecs_entity_t delay_event(ecs_world_t *world, void (*value)(ecs_world_t*, const ecs_entity_t), const ecs_entity_t e, const double delay) {
    zox_neww(event)
    zox_set(event, TimedEvent, { value })
    zox_set(event, EventInput, { e })
    zox_set(event, EventTime, { delay })
    return event;
}

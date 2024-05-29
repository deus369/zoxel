void delay_event(ecs_world_t *world, void (*value)(ecs_world_t*, const ecs_entity_t), const ecs_entity_t e, const double delay) {
    const ecs_entity_t event = ecs_new(world, 0);
    zox_set(event, TimedEvent, { value })
    zox_set(event, EventInput, { e })
    zox_set(event, EventTime, { delay })
}

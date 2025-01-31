void button_event_close_window(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t parent = zox_get_value(event->clicked, ParentLink)
    const ecs_entity_t parents_parent = zox_get_value(parent, ParentLink)
    ecs_entity_t window = parents_parent;
    zox_delete(window)
}

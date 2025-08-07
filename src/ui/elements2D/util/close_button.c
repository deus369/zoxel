void button_event_close_window(ecs *world, const ClickEventData *event) {
    const entity parent = zox_get_value(event->clicked, ParentLink)
    const entity parents_parent = zox_get_value(parent, ParentLink)
    entity window = parents_parent;
    zox_delete(window)
}

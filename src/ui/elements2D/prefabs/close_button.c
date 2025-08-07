extern void button_event_close_window(ecs *world, const ClickEventData *event);

entity spawn_prefab_button_close(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("header")
    zox_add_tag(e, CloseButton)
    zox_prefab_set(e, ClickEvent, { &button_event_close_window })
    return e;
}
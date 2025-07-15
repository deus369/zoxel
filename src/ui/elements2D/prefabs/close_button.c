extern void button_event_close_window(ecs_world_t *world, const ClickEventData *event);

ecs_entity_t spawn_prefab_button_close(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("header")
    zox_add_tag(e, CloseButton)
    zox_prefab_set(e, ClickEvent, { &button_event_close_window })
    return e;
}
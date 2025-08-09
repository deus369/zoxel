ecs_entity_t generic_event_prefab;

void spawn_prefab_generic_event(ecs_world_t *world) {
    zox_prefab();
    zox_prefab_name("generic_event");
    zox_add_tag(e, DestroyInFrame);
    zox_prefab_set(e, GenericEvent, { 0 });
    generic_event_prefab = e;
}

ecs_entity_t spawn_generic_event(ecs_world_t *world, byte state) {
    zox_instance(generic_event_prefab);
    zox_name("event");
    zox_set(e, GenericEvent, { state });
    return e;
}

void button_event_close_window(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // zoxel_log(" > closing window\n");
    const ParentLink *parentLink = ecs_get(world, trigger_entity, ParentLink);
    const ParentLink *parentParentLink = ecs_get(world, parentLink->value, ParentLink);
    ecs_entity_t window = parentParentLink->value;
    zox_delete(window)
}
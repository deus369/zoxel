void button_event_close_window(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element) {
    // zoxel_log(" > closing window\n");
    const ecs_entity_t parent = zox_get_value(element, ParentLink)
    const ecs_entity_t parents_parent = zox_get_value(parent, ParentLink)
    ecs_entity_t window = parents_parent;
    zox_delete(window)
}

void set_element_dragged(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_t element, const unsigned char drag_mode) {
    DraggableState *dragableState = zox_get_mut(element, DraggableState)
    if (!dragableState->value) {
        DraggerLink *draggerLink = zox_get_mut(element, DraggerLink)
        dragableState->value = drag_mode;
        draggerLink->value = player;
        zox_modified(element, DraggableState)
        zox_modified(element, DraggerLink)
#ifdef zox_log_ui_dragging
        zox_log(" > ui dragging at [%f]\n", (float) zox_current_time)
#endif
    }
}

void drag_element(ecs_world_t *world, ecs_entity_t e, int2 drag_value) {
    if (!zox_valid(e)) return;
    PixelPosition *pixel_position = zox_get_mut(e, PixelPosition)
    pixel_position->value.x += drag_value.x;
    pixel_position->value.y += drag_value.y;
    if (zox_has(e, DraggableLimits)) {
        const DraggableLimits *draggableLimits = zox_get(e, DraggableLimits)
        if (pixel_position->value.x < -draggableLimits->value.x) pixel_position->value.x = -draggableLimits->value.x;
        if (pixel_position->value.x > draggableLimits->value.x) pixel_position->value.x = draggableLimits->value.x;
        if (pixel_position->value.y < -draggableLimits->value.y) pixel_position->value.y = -draggableLimits->value.y;
        if (pixel_position->value.y > draggableLimits->value.y) pixel_position->value.y = draggableLimits->value.y;
    }
    zox_modified(e, PixelPosition)
    #ifdef zox_log_ui_dragging
        zox_log(" > dragging window [%lu] by %ix%i\n", e, drag_value.x, drag_value.y)
    #endif
}

// if pixel position moves, update real position
// if it updates, also update any childrens positions too
// has to also move children and their children
//! Plays a Sound when button is clicked
void ElementDragSystem(ecs_iter_t *it) {
    zox_iter_world()
    const DraggableState *dragableStates = ecs_field(it, DraggableState, 1);
    const DraggingDelta *draggingDeltas = ecs_field(it, DraggingDelta, 2);
    const DraggedLink *draggedLinks = ecs_field(it, DraggedLink, 3);
    for (int i = 0; i < it->count; i++) {
        const DraggableState *dragableState = &dragableStates[i];
        if (dragableState->value) {
            const DraggingDelta *draggingDelta = &draggingDeltas[i];
            if (draggingDelta->value.x != 0 || draggingDelta->value.y != 0) {
                const DraggedLink *draggedLink = &draggedLinks[i];
                ecs_entity_t dragged_entity = draggedLink->value;
                if (!dragged_entity) dragged_entity = it->entities[i];
                drag_element(world, dragged_entity, draggingDelta->value);
            }
        }
    }
} zox_declare_system(ElementDragSystem)

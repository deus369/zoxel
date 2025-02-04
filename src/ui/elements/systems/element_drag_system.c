// if pixel position moves, update real position
// if it updates, also update any childrens positions too
// has to also move children and their children
void ElementDragSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DraggableState, dragableStates, 1)
    zox_field_in(DraggingDelta, draggingDeltas, 2)
    zox_field_in(DraggedLink, draggedLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DraggableState, dragableStates, dragableState)
        if (dragableState->value) {
            zox_field_i(DraggingDelta, draggingDeltas, draggingDelta)
            if (draggingDelta->value.x != 0 || draggingDelta->value.y != 0) {
                zox_field_e()
                zox_field_i(DraggedLink, draggedLinks, draggedLink)
                ecs_entity_t dragged_entity = draggedLink->value;
                if (!dragged_entity) dragged_entity = e;
                drag_element(world, dragged_entity, draggingDelta->value);
            }
        }
    }
} zox_declare_system(ElementDragSystem)

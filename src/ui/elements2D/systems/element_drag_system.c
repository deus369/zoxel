// if pixel position moves, update real position
// if it updates, also update any childrens positions too
// has to also move children and their children
void ElementDragSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DraggableState)
    zox_sys_in(DraggingDelta)
    zox_sys_in(DraggedLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(DraggableState, dragableState)
        zox_sys_i(DraggingDelta, draggingDelta)
        zox_sys_i(DraggedLink, draggedLink)
        if (!dragableState->value) {
            continue;
        }
        if (draggingDelta->value.x != 0 || draggingDelta->value.y != 0) {
            entity dragged_entity = draggedLink->value;
            if (!dragged_entity) {
                dragged_entity = e;
            }
            // zox_log("[%s] is now dragging [%s] by ", zox_get_name(e), zox_get_name(dragged_entity))
            // zox_log("> dragging [%s] [%ix%i]", zox_get_name(dragged_entity), draggingDelta->value.x, draggingDelta->value.y)
            drag_element(world, dragged_entity, draggingDelta->value);
        }
    }
} zox_declare_system(ElementDragSystem)

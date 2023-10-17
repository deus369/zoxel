// pushes mouse->delta into DraggingDelta's ui component
// todo: check device mode here or device enabled states
void DraggerEndSystem(ecs_iter_t *it) {
    DragableState *dragableStates = ecs_field(it, DragableState, 1);
    DraggerLink *draggerLinks = ecs_field(it, DraggerLink, 2);
    DraggingDelta *draggingDeltas = ecs_field(it, DraggingDelta, 3);
    for (int i = 0; i < it->count; i++) {
        DraggerLink *draggerLink = &draggerLinks[i];
        if (draggerLink->value == 0) continue;
        DragableState *dragableState = &dragableStates[i];
        if (dragableState->value == 0) continue;
        DraggingDelta *draggingDelta = &draggingDeltas[i];
        ecs_entity_t player_entity = draggerLink->value;
        const DeviceLinks *deviceLinks = ecs_get(it->world, player_entity, DeviceLinks);
        unsigned char did_drag_end = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            ecs_entity_t device_entity = deviceLinks->value[j];
            if (dragableState->value == 1 && zox_has(device_entity, Mouse)) {
                const Mouse *mouse = ecs_get(world, device_entity, Mouse);
                if (mouse->left.released_this_frame) did_drag_end = 1;
                else if (mouse->left.is_pressed) draggingDelta->value = mouse->delta;
            } else if (dragableState->value == 2 && zox_has(device_entity, Touchscreen)) {
                const Children *zevices = ecs_get(world, device_entity, Children);
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = ecs_get(world, zevice_entity, ZevicePointer);
                        if (devices_get_released_this_frame(zevicePointer->value)) did_drag_end = 1;
                        else if (devices_get_is_pressed(zevicePointer->value)) draggingDelta->value = ecs_get(world, zevice_entity, ZevicePointerDelta)->value;
                        break;
                    }
                }
            }
        }
        if (did_drag_end) {
            dragableState->value = 0;
            draggerLink->value = 0;
            draggingDelta->value = (int2) { 0, 0 };
        }
    }
} zox_declare_system(DraggerEndSystem)

/*const Touchscreen *touchscreen = ecs_get(world, device_entity, Touchscreen);
if (touchscreen->primary_touch.value.released_this_frame) {
    DragableState *dragableState = &dragableStates[i];
    dragableState->value = 0;
    draggerLink->value = 0;
    draggingDelta->value = (int2) { 0, 0 };
} else if (touchscreen->primary_touch.value.is_pressed) {
    draggingDelta->value = touchscreen->primary_touch.delta;
}*/

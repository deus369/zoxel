void DraggerEndSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_out(DraggableState, dragableStates, 1)
    zox_field_out(DraggerLink, draggerLinks, 2)
    zox_field_out(DraggingDelta, draggingDeltas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(DraggerLink, draggerLinks, draggerLink)
        if (draggerLink->value == 0) continue;
        zox_field_o(DraggableState, dragableStates, dragableState)
        if (dragableState->value == 0) continue;
        zox_field_o(DraggingDelta, draggingDeltas, draggingDelta)
        const ecs_entity_t player_entity = draggerLink->value;
        const DeviceLinks *deviceLinks = zox_get(player_entity, DeviceLinks)
        unsigned char did_drag_end = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (dragableState->value == zox_drag_mode_mouse && zox_has(device_entity, Mouse)) {
                zox_geter(device_entity, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if ( !zox_has(zevice, ZevicePointer)) continue;
                    const unsigned char click = zox_get_value(zevice, ZevicePointer)
                    const int2 delta = zox_get_value(zevice, ZevicePointerDelta)
                    if (devices_get_released_this_frame(click)) did_drag_end = 1;
                    else if (devices_get_is_pressed(click)) draggingDelta->value = delta;
                }
            } else if (dragableState->value == zox_drag_mode_finger && zox_has(device_entity, Touchscreen)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
                        if (devices_get_released_this_frame(zevicePointer->value)) did_drag_end = 1;
                        else if (devices_get_is_pressed(zevicePointer->value)) draggingDelta->value = zox_get_value(zevice_entity, ZevicePointerDelta);
                        break;
                    }
                }
            }
        }
        if (did_drag_end) {
            dragableState->value = 0;
            draggerLink->value = 0;
            draggingDelta->value = int2_zero;
#ifdef zox_log_ui_dragging
            zox_log(" > ui dragging ended at [%f]\n", (float) zox_current_time)
#endif
        }
    }
} zox_declare_system(DraggerEndSystem)

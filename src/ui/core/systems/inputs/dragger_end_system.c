void DraggerEndSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_out(DraggableState)
    zox_sys_out(DraggerLink)
    zox_sys_out(DraggingDelta)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(DraggerLink, draggerLink)
        zox_sys_o(DraggableState, dragableState)
        zox_sys_o(DraggingDelta, draggingDelta)
        if (draggerLink->value == 0 || dragableState->value == 0) {
            continue;
        }
        const entity player_entity = draggerLink->value;
        const DeviceLinks *deviceLinks = zox_get(player_entity, DeviceLinks)
        byte did_drag_end = 0;
        for (int j = 0; j < deviceLinks->length; j++) {
            const entity device = deviceLinks->value[j];
            if (!zox_valid(device) || zox_gett_value(device, DeviceDisabled)) {
                continue;
            }
            zox_geter(device, Children, zevices)
            for (int k = 0; k < zevices->length; k++) {
                const entity zevice = zevices->value[k];
                if (!zevice) {
                    continue;
                }
                if (!zox_has(zevice, ZevicePointer)) {
                    continue;
                }
                const byte click = zox_get_value(zevice, ZevicePointer)
                const int2 delta = zox_get_value(zevice, ZevicePointerDelta)
                if (devices_get_released_this_frame(click)) {
                    did_drag_end = 1;
                } else if (devices_get_is_pressed(click)) {
                    draggingDelta->value = delta;
                }
            }

            /*if (dragableState->value == zox_drag_mode_mouse && zox_has(device, Mouse)) {

            } else if (dragableState->value == zox_drag_mode_finger && zox_has(device, Touchscreen)) {
                const Children *zevices = zox_get(device, Children)
                for (int k = 0; k < zevices->length; k++) {
                    entity zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
                        if (devices_get_released_this_frame(zevicePointer->value)) did_drag_end = 1;
                        else if (devices_get_is_pressed(zevicePointer->value)) draggingDelta->value = zox_get_value(zevice_entity, ZevicePointerDelta);
                        break;
                    }
                }
            }*/
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

#ifdef zoxel_inputs
void ElementActivateSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinks, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(RaycasterTarget, raycasterTargets, 3)
    zox_field_out(RaycasterResult, raycasterResults, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(RaycasterResult, raycasterResults, raycasterResult)
        zox_field_i_in(RaycasterTarget, raycasterTargets, raycasterTarget)
        if (!raycasterTarget->value || !ecs_is_alive(world, raycasterTarget->value)) {
            raycasterResult->value = 0;
            continue;
        }
        zox_field_e()
        zox_field_i_in(DeviceLinks, deviceLinks, deviceLinks2)
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        unsigned char did_drag = 0;
        unsigned char did_activate = 0;
        for (int j = 0; j < deviceLinks2->length; j++) { // convert inputs to actions
            ecs_entity_t device_entity = deviceLinks2->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (mouse->left.pressed_this_frame) did_drag = zox_drag_mode_mouse;
                else if (mouse->left.released_this_frame) did_activate = 1;
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device_entity, Gamepad)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZeviceButton)) {
                        const DeviceButtonType *deviceButtonType = zox_get(zevice_entity, DeviceButtonType)
                        if (deviceButtonType->value == zox_device_button_a) {
                            const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                            if (!zeviceDisabled->value) {
                                const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                                if (devices_get_pressed_this_frame(zeviceButton->value)) did_activate = 1;
                            }
                            break;
                        }
                    }
                }
            } else if (deviceMode->value == zox_device_mode_touchscreen && zox_has(device_entity, Touchscreen)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
                        if (devices_get_pressed_this_frame(zevicePointer->value)) {
                            did_drag = zox_drag_mode_finger;
                        } else if (devices_get_released_this_frame(zevicePointer->value)) {
                            did_activate = 1;
                        }
                        break;
                    }
                }
            }
        }
        raycasterResult->value = did_drag || did_activate;
        if (did_drag) {
            if (zox_has(raycasterTarget->value, Dragable)) {
                DraggableState *dragableState = zox_get_mut(raycasterTarget->value, DraggableState)
                if (!dragableState->value) {
                    DraggerLink *draggerLink = zox_get_mut(raycasterTarget->value, DraggerLink)
                    dragableState->value = did_drag;
                    draggerLink->value = e;
                    zox_modified(raycasterTarget->value, DraggableState)
                    zox_modified(raycasterTarget->value, DraggerLink)
#ifdef zox_log_ui_dragging
                    zox_log(" > ui dragging at [%f]\n", (float) zox_current_time)
#endif
                }
            }
        } else if (did_activate) set_ui_clicked_mut(world, raycasterTarget->value);
    }
} zox_declare_system(ElementActivateSystem)
#endif

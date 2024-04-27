#ifdef zoxel_inputs
void ElementActivateSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_in(RaycasterTarget, raycasterTargets, 3)
    zox_field_out(RaycasterResult, raycasterResults, 4)
    zox_field_out(ClickingEntity, clickingEntitys, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(RaycasterResult, raycasterResults, raycasterResult)
        zox_field_i_out(ClickingEntity, clickingEntitys, clickingEntity)
        zox_field_i_in(RaycasterTarget, raycasterTargets, raycasterTarget)
        const ecs_entity_t element = raycasterTarget->value;
        if (!zox_alive(element)) { // failsafe
            clickingEntity->value = 0;
            raycasterResult->value = 0;
            continue;
        }
        if (!element) continue;
        zox_field_e()
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        unsigned char did_drag = 0;
        unsigned char did_activate = 0;
        for (int j = 0; j < deviceLinks->length; j++) { // convert inputs to actions
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (deviceMode->value == zox_device_mode_keyboardmouse && zox_has(device_entity, Mouse)) {
                const Mouse *mouse = zox_get(device_entity, Mouse)
                if (mouse->left.pressed_this_frame) {
                    clickingEntity->value = element;
                    did_drag = zox_drag_mode_mouse;
                }
                else if (mouse->left.released_this_frame) {
                    if (element == clickingEntity->value) did_activate = 1;
                    clickingEntity->value = 0; // end 'event'
                }
            } else if (deviceMode->value == zox_device_mode_gamepad && zox_has(device_entity, Gamepad)) {
                const Children *zevices = zox_get(device_entity, Children)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice_entity = zevices->value[k];
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
                    const ecs_entity_t zevice_entity = zevices->value[k];
                    if (zox_has(zevice_entity, ZevicePointer)) {
                        const ZevicePointer *zevicePointer = zox_get(zevice_entity, ZevicePointer)
                        if (devices_get_pressed_this_frame(zevicePointer->value)) {
                            did_drag = zox_drag_mode_finger;
                            clickingEntity->value = element;
                        } else if (devices_get_released_this_frame(zevicePointer->value)) {
                            if (element == clickingEntity->value) did_activate = 1;
                        }
                        break;
                    }
                }
            }
        }
        raycasterResult->value = did_drag || did_activate;
        if (did_drag) {
            if (zox_has(element, Dragable)) {
                DraggableState *dragableState = zox_get_mut(element, DraggableState)
                if (!dragableState->value) {
                    DraggerLink *draggerLink = zox_get_mut(element, DraggerLink)
                    dragableState->value = 1;
                    draggerLink->value = e;
                    zox_modified(element, DraggableState)
                    zox_modified(element, DraggerLink)
#ifdef zox_log_ui_dragging
                    zox_log(" > ui dragging at [%f]\n", (float) zox_current_time)
#endif
                }
            }
        } else if (did_activate) set_ui_clicked_mut(world, element);
    }
} zox_declare_system(ElementActivateSystem)
#endif
